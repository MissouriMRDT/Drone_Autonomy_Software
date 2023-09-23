/******************************************************************************
 * @brief Defines functions and objects used project wide.
 *
 * @file AutonomyGlobals.h
 * @author Eli Byrd (edbgkk@mst.edu), ClayJay3 (claytonraycowen@gmail.com)
 * @date 2023-06-20
 *
 * @copyright Copyright Mars Rover Design Team 2023 - All Rights Reserved
 ******************************************************************************/

#ifndef AUTONOMY_GLOBALS_H
#define AUTONOMY_GLOBALS_H

#include "AutonomyConstants.h"
#include "IdentitySoftware.h"
#include "threads/CameraHandlerThread.h"

#include <chrono>
#include <ctime>
#include <iostream>

#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/event.hpp>
#include <boost/statechart/state.hpp>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/transition.hpp>

#include <boost/mpl/list.hpp>

namespace sc  = boost::statechart;
namespace mpl = boost::mpl;

// Versioning:
extern IdentitySoftware g_pIdentifySoftware;    // Global Version Handler

// Camera Handler:
extern CameraHandlerThread* g_pCameraHandler;

#endif    // AUTONOMY_GLOBALS_H
