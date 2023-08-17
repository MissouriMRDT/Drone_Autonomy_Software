/******************************************************************************
 * @brief State Machine Implementation for Drone Autonomy Software
 *
 * @file StateMachine.hpp
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2023-07-31
 *
 * @copyright Copyright MRDT 2023 - All Rights Reserved
 ******************************************************************************/

#include "../AutonomyGlobals.h"

// Forward References
struct IdleState;

/******************************************************************************
 * @brief State Machine Object
 *
 *        The State Machine is what controls the operation of the our
 *        Rover Autonomously. Though the state handlers below and attached
 *        transitions the Rover navigates though many algorithms to
 *        complete the Autonomous task.
 *
 *
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2023-07-31
 ******************************************************************************/
struct StateMachine : sc::state_machine<StateMachine, IdleState>
{
        StateMachine() { LOG_INFO(g_qSharedLogger, "Starting State Machine..."); }
};

/******************************************************************************
 * @brief Idle State Handler and Transition Forward Declarations
 *
 *        Adds the state handler and transitions for the Idle State.
 *
 *
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2023-07-31
 ******************************************************************************/


#include "../states/IdleState.hpp"
