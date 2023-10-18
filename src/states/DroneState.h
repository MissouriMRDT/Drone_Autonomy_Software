#ifndef DRONESTATE_H
#define DRONESTATE_H

#include <mavsdk/mavsdk.h>
#include <mavsdk/plugins/action/action.h>
#include <mavsdk/plugins/mission/mission.h>
#include <mavsdk/plugins/telemetry/telemetry.h>

#include <iostream>

using namespace mavsdk;

class DroneState
{
private:
    double drone_latitude_deg;
    double drone_longitude_deg;
    float drone_relative_altitude_m;
    float gimbal_pitch_deg;
    float gimbal_yaw_deg;

public:

    //Default Constructor 

    DroneState(): drone_latitude_deg(0), drone_longitude_deg(0), drone_relative_altitude_m(0), gimbal_pitch_deg(0), gimbal_yaw_deg(0) {};


    void waypoint(double latitude_deg,
    double longitude_deg,
    float relative_altitude_m,
    float speed_m_s,
    bool is_fly_through,
    float gimbal_pitch_deg,
    float gimbal_yaw_deg,
    Mission::MissionItem::CameraAction None);

    
    void takeoff(float m);

    void land();

    void updatestate();
};

#endif