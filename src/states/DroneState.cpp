#ifndef DRONESTATE_CPP
#define DRONESTATE_CPP

#include <vector>
#include <chrono>
#include <cstdint>
#include <future>
#include <iostream>
#include <mavsdk/mavsdk.h>
#include <mavsdk/plugins/action/action.h>
#include <mavsdk/plugins/telemetry/telemetry.h>
#include <memory>
#include <thread>
#include <mavsdk/plugins/mission/mission.h>
#include "DroneState.h"

using namespace mavsdk;

Mission::MissionItem make_mission_item(
    double latitude_deg,
    double longitude_deg,
    float relative_altitude_m,
    float speed_m_s,
    bool is_fly_through,
    float gimbal_pitch_deg,
    float gimbal_yaw_deg,
    Mission::MissionItem::CameraAction camera_action)
{
    Mission::MissionItem new_item{};
    new_item.latitude_deg = latitude_deg;
    new_item.longitude_deg = longitude_deg;
    new_item.relative_altitude_m = relative_altitude_m;
    new_item.speed_m_s = speed_m_s;
    new_item.is_fly_through = is_fly_through;
    new_item.gimbal_pitch_deg = gimbal_pitch_deg;
    new_item.gimbal_yaw_deg = gimbal_yaw_deg;
    new_item.camera_action = camera_action;
    return new_item;

}

void DroneState::waypoint(double latitude_deg,
                          double longitude_deg,
                          float relative_altitude_m,
                          float speed_m_s,
                          bool is_fly_through,
                          float gimbal_pitch_deg,
                          float gimbal_yaw_deg,
                          Mission::MissionItem::CameraAction camera_action)
    {
        std::vector<Mission::MissionItem> mission_items;

        mission_items.push_back(make_mission_item(
            latitude_deg,
            longitude_deg,
            relative_altitude_m,
            speed_m_s,
            is_fly_through,
            gimbal_pitch_deg,
            gimbal_yaw_deg,
            camera_action));
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

    int main()
    {
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

#endif