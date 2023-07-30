\mainpage

# Autonomy Software

Welcome to the Autonomy Software repository of the Mars Rover Design Team (MRDT) at Missouri University of Science and Technology (Missouri S&T)! This repository contains the source code, documentation, and other resources for the development of the Autonomy Software for our Mars Rover. The Autonomy Software project aims to compete in the University Rover Challenge (URC) by demonstrating advanced autonomous capabilities and robust navigation algorithms.

### API Documentation
Everytime a commit is made to the development branch, a GitHub Action is ran that autonomatically generates documentation for files, classes, methods, functions, namespaces, etc. using Doxygen. To ensure that Doxygen can properly document and use your comments, make sure to use the documentation templates HERE. If you're running the development container in VSCode the templates can be automatically generated by typing `/**<enter>`. Regardless, all file, method, and function documentation must be use the template's style across the whole project.

#### [Autonomy_Software API Docs HERE](https://missourimrdt.github.io/Autonomy_Software/)


## Overview

The Autonomy Software project is organized into different directories, each serving a specific purpose. Here's a brief overview of the directories:

- **algorithms**: Contains C++ files related to the algorithms used in our Rover project. These files implement the core functionality and logic necessary for autonomous navigation, perception, and decision-making.

- **interfaces**: Contains C++ files related to the physical systems, boards, microcontrollers, or sensors on our Rover. These files handle the communication and interaction with external hardware components, ensuring seamless integration and data exchange.

- **states**: Contains C++ files related to the state machine code of our Rover. These files define the different states and transitions that govern the Rover's behavior, allowing for efficient task execution and adaptability to changing conditions.

- **util**: Contains utility scripts and helper functions used in our Rover project. These files provide various tools and functionalities to support development, debugging, and project management tasks, increasing overall efficiency and code reusability.

- **vision**: Contains C++ files related to vision processing or computer vision algorithms used in our Rover. These files enable the Rover to process visual data, such as images or videos, and extract meaningful information for autonomous navigation and object recognition.

- **tests**: Contains test cases and test scripts to ensure the correctness and reliability of our Autonomy Software. These files help validate the functionality and performance of our code, ensuring robustness and accuracy in real-world scenarios.

- **tools**: Contains files that provide utility scripts, development tools, or miscellaneous functionalities for our project. These files assist in various development tasks, such as data analysis, visualization, or simulation, enhancing the overall development experience.

- **external**: Contains external dependencies, libraries, or third-party modules used in our Rover project. These files are essential for the project's functionality and are organized based on their purpose or source, ensuring proper integration and compliance with licensing requirements.

- **examples**: Contains example code snippets, demos, or sample implementations related to our Rover project. These files showcase specific functionalities, best practices, or usage scenarios, helping us understand and leverage the capabilities of our Autonomy Software effectively.

- **docs**: Contains documentation files and resources for our Rover project. These files provide comprehensive and accessible documentation to guide developers, users, and contributors in understanding, configuring, and extending the Autonomy Software.

- **data**: Contains data files and resources used in our Rover project. These files include sensor data, training data, configuration files, map data, simulation data, and log files, facilitating the development, testing, and analysis of our autonomy algorithms.

The **src** directory serves as the main source code directory and contains the algorithms, interfaces, states, util, and vision directories mentioned above.

## Getting Started

To get started with our Autonomy Software development, follow these steps:

1. Download and install required software:
    - Download and install Visual Studio Code from [here](https://code.visualstudio.com/download)
    - Download and install git-scm from [here](https://git-scm.com/downloads)

    NOTE: For all installs, select the ADD TO PATH options whenever available.
   

2. Navigate to the cloned directory:
   ```
   cd Autonomy_Software
   ```

3. Explore the different directories to understand the structure and purpose of each.

4. Refer to the specific README files within each directory for detailed information and guidelines on organizing files and using the functionalities.

5. Install any required dependencies or external libraries mentioned in the documentation or README files.

6. Start developing


# Debugging with CMake and Visual Studio Code

Debugging a C++ application in Visual Studio Code can be made seamless and efficient using the CMakeTools extension from Microsoft, which was automatically installed into the devcontainer from the Visual Studio Code Extensions Marketplace. This extension integrates CMake with Visual Studio Code, enabling developers to easily build and debug C++ applications directly within the VSCode environment.

## Setting up the Development Environment

1. Open this project in a devcontainer: First, install Microsoft's ~Dev Containers~ extension from the marketplace. Then hit `CTRL + SHIFT + P` sequence
to open the editor commands, and select the `Dev Container: Rebuild Container` option. 

3. Select the CMake Kit: Once you open the project, you'll be prompted to select the CMake Kit for your project. You can do this either from the bottom status bar or during the initial setup of the development container a prompt will automatically show up. The CMake Kit represents the C++ toolchain used for building the project (compiler, architecture, etc.). Choose the appropriate kit for your project.
| ![](data/README_Resources/images/kit_selection_first_container_start.png) | 
|:--:| 
| *When the devcontainer is first started CMAKE Tools will ask you to select a kit. The compiler located at /usr/bin/g++ and /usr/bin/gcc will always be the safest choice.* |
| ![](data/README_Resources/images/kit_selection_toolbar.png) |  
| *During subsequent startups, you can easily change the kit using the bottom toolbar.* |

4. Configure and build the project: If the CMake cache needs to be generated or updated, the extension will configure the project automatically. This process may take a few seconds, depending on your hardware.
| ![](data/README_Resources/images/toolbar_build_run.png) | 
|:--:| 
| *Use the buttons in the toolbar to build and run the Autonomy_Software application.* |

## Debugging the C++ Application

Now that you have set up the development environment, you are ready to debug your C++ application.

1. Set Breakpoints: Place breakpoints in your C++ source code where you want to pause the program's execution to inspect variables, analyze the flow, or 
diagnose issues.

| ![](data/README_Resources/images/breakpoint_selection.png) | 
|:--:| 
| *To set breakpoints directly within the vscode editor, toggle on the red dot next to the line numbers.* |

2. Compile for Debugging: In order to properly debug our application, we must compile the program with special flags set. We can let CMAKE do this for us by simply selecting the debug configuration from the bottom toolbar.
| ![](data/README_Resources/images/toolbar_cmake_debug_config.png) | 
|:--:| 
| *Use the toolbar to change between Release and Debug configurations. Release runs faster but can't be debugged, so whenever you're done debugging switch back to the Release config.* |

2. Start Debugging: Click the debug icon in the toolbar to automatically build and start the program.
| ![](data/README_Resources/images/toolbar_debug_button.png) | 
|:--:| 
| *Click the debug button to enter debug mode in VSCode.* |

3. Debugging Controls: Use the debugging controls (e.g., step into, step over, continue, etc.) in the Debug toolbar to navigate through your code while inspecting variables, stack traces, and more.
![](data/README_Resources/images/vscode_debug_mode.png)

- Inspect Variables: In the "Variables" view, you can inspect the current values of variables in your code during debugging.
- Analyze Call Stack: The "Call Stack" view provides a stack trace, helping you understand the flow of execution and identify the function calls that led to the current point in your code.
- Set Watchpoints: You can set watchpoints on specific variables to break execution when their values change.
- Debug Console: Use the Debug Console to execute custom expressions and commands during debugging.

With CMakeTools and Visual Studio Code, you can efficiently build and debug your C++ applications within the familiar and powerful VSCode environment. The seamless integration between CMake and Visual Studio Code makes it easier for C++ developers to focus on writing code and quickly diagnose and fix issues. Happy debugging!

