/******************************************************************************
 * @brief Idle State Implementation for Drone Autonomy State Machine
 *
 * @file IdleState.hpp
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2023-07-31
 *
 * @copyright Copyright Mars Rover Design Team 2023 - All Rights Reserved
 ******************************************************************************/

#include "../AutonomyGlobals.h"

/******************************************************************************
 * @brief Idle State Handler
 *
 *        Primarily the Idle State Handler, handles the routing that
 *        occures at the beginning of each leg. This is also the state
 *        which Drone Autonomy will sit in if moving.
 *
 *        It also listens for state events that pertain to the Idle State
 *        and calls the approprate transition handler to transition states
 *        as needed.
 *
 *
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2023-07-31
 ******************************************************************************/
struct IdleState : sc::simple_state<IdleState, StateMachine>
{
        IdleState() { LOG_INFO(g_qSharedLogger, "In State: Idle"); }
};
