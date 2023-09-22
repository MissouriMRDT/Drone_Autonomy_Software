/******************************************************************************
 * @brief Main program file. Sets up classes and runs main program functions.
 *
 * @file main.cpp
 * @author Eli Byrd (edbgkk@mst.edu), ClayJay3 (claytonraycowen@gmail.com)
 * @date 2023-06-20
 *
 * @copyright Copyright Mars Rover Design Team 2023 - All Rights Reserved
 ******************************************************************************/

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <chrono>
#include <cstdint>
#include <future>
#include <iostream>
#include <mavsdk/mavsdk.h>
#include <mavsdk/plugins/action/action.h>
#include <mavsdk/plugins/telemetry/telemetry.h>
#include <memory>
#include <thread>

#include "./AutonomyGlobals.h"
#include "./AutonomyLogging.h"
#include "./interfaces/StateMachine.hpp"

// Check if any file from the example directory has been included.
// If not included, define empty run example function and set bRunExampleFlag
// to false. If included, then define bRunExampleFlag as true.
#ifndef CHECK_IF_EXAMPLE_INCLUDED
static bool bRunExampleFlag = false;

void RunExample() {}
#else
CHECK_IF_EXAMPLE_INCLUDED
#endif

void usage(const std::string& bin_name)
{
    std::cerr << "Usage : " << bin_name << " <connection_url>\n"
              << "Connection URL format should be :\n"
              << " For TCP : tcp://[server_host][:server_port]\n"
              << " For UDP : udp://[bind_host][:bind_port]\n"
              << " For Serial : serial:///path/to/serial/dev[:baudrate]\n"
              << "For example, to connect to the simulator use URL: udp://:14540\n";
}

std::shared_ptr<mavsdk::System> get_system(mavsdk::Mavsdk& mavsdk)
{
    std::cout << "Waiting to discover system...\n";
    auto prom = std::promise<std::shared_ptr<mavsdk::System>>{};
    auto fut  = prom.get_future();

    // We wait for new systems to be discovered, once we find one that has an
    // autopilot, we decide to use it.
    mavsdk.subscribe_on_new_system(
        [&mavsdk, &prom]()
        {
            auto system = mavsdk.systems().back();

            if (system->has_autopilot())
            {
                std::cout << "Discovered autopilot\n";

                // Unsubscribe again as we only want to find one system.
                mavsdk.subscribe_on_new_system(nullptr);
                prom.set_value(system);
            }
        });

    // We usually receive heartbeats at 1Hz, therefore we should find a
    // system after around 3 seconds max, surely.
    if (fut.wait_for(std::chrono::seconds(3)) == std::future_status::timeout)
    {
        std::cerr << "No autopilot found.\n";
        return {};
    }

    // Get discovered system now.
    return fut.get();
}

/******************************************************************************
 * @brief Drone Autonomy main function.
 *
 * @return int - Exit status number.
 *
 * @author Eli Byrd (edbgkk@mst.edu), ClayJay3 (claytonraycowen@gmail.com)
 * @date 2023-06-20
 ******************************************************************************/
int main()
{
    // Print Software Header
    std::ifstream fHeaderText("../data/ASCII/v24.txt");
    std::string szHeaderText;
    if (fHeaderText)
    {
        std::ostringstream pHeaderText;
        pHeaderText << fHeaderText.rdbuf();
        szHeaderText = pHeaderText.str();
    }

    std::cout << szHeaderText << std::endl;
    std::cout << "Copyright \u00A9 2023 - Mars Rover Design Team\n" << std::endl;

    // Initialize Loggers
    InitializeLoggers();

    // Check whether or not we should run example code or continue with normal operation.
    if (bRunExampleFlag)
    {
        RunExample();
    }
    else
    {
        // TODO: Initialize Threads

        // TODO: Initialize RoveComm

        // MAVSDK Test
        using namespace mavsdk;

        Mavsdk mavsdk;
        ConnectionResult connection_result = mavsdk.add_any_connection("udp://:14540");

        if (connection_result != ConnectionResult::Success)
        {
            std::cerr << "Connection failed: " << connection_result << '\n';
            return 1;
        }

        auto system = get_system(mavsdk);
        if (!system)
        {
            return 1;
        }

        // Instantiate plugins.
        auto telemetry = Telemetry{system};
        auto action    = Action{system};

        // We want to listen to the altitude of the drone at 1 Hz.
        const auto set_rate_result = telemetry.set_rate_position(1.0);
        if (set_rate_result != Telemetry::Result::Success)
        {
            std::cerr << "Setting rate failed: " << set_rate_result << '\n';
            return 1;
        }

        // Set up callback to monitor altitude while the vehicle is in flight
        telemetry.subscribe_position([](Telemetry::Position position) { std::cout << "Altitude: " << position.relative_altitude_m << " m\n"; });

        // Check until vehicle is ready to arm
        while (telemetry.health_all_ok() != true)
        {
            std::cout << "Vehicle is getting ready to arm\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        // Arm vehicle
        std::cout << "Arming...\n";
        const Action::Result arm_result = action.arm();

        if (arm_result != Action::Result::Success)
        {
            std::cerr << "Arming failed: " << arm_result << '\n';
            return 1;
        }

        // Take off
        std::cout << "Taking off...\n";
        const Action::Result takeoff_result = action.takeoff();
        if (takeoff_result != Action::Result::Success)
        {
            std::cerr << "Takeoff failed: " << takeoff_result << '\n';
            return 1;
        }

        // Let it hover for a bit before landing again.
        std::this_thread::sleep_for(std::chrono::seconds(10));

        std::cout << "Landing...\n";
        const Action::Result land_result = action.land();
        if (land_result != Action::Result::Success)
        {
            std::cerr << "Land failed: " << land_result << '\n';
            return 1;
        }

        // Check if vehicle is still in air
        while (telemetry.in_air())
        {
            std::cout << "Vehicle is landing...\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        std::cout << "Landed!\n";

        // We are relying on auto-disarming but let's keep watching the telemetry for a bit longer.
        std::this_thread::sleep_for(std::chrono::seconds(3));
        std::cout << "Finished...\n";

        return 0;
    }

    return 0;
}
