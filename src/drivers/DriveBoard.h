/******************************************************************************
 * @brief Defines the driver for sending commands to the drive board on
 * 		the Rover.
 *
 * @file DriveBoard.h
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2023-06-18
 *
 * @copyright Copyright Mars Rover Design Team 2023 - All Rights Reserved
 ******************************************************************************/

#ifndef DRIVEBOARD_H
#define DRIVEBOARD_H

#include <vector>

class DriveBoard
{
    private:
        int m_iTargetSpeedLeft;
        int m_iTargetSpeedRight;

    public:
        DriveBoard();
        ~DriveBoard();

        std::vector<int> CalculateMove(float fSpeed, float fAngle);
        void SendDrive(int iLeftTarget, int iRightTarget);
        void SendStop();
};

#endif    // DRIVEBOARD_H
