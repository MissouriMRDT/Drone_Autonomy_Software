#!/bin/bash

# Define the path to the executable
if [ "$1" = "GitHub-Action" ]; then
  executable_path="/opt/Drone_Autonomy_Software/build/Drone_Autonomy_Software"
else
  executable_path="/workspaces/Drone_Autonomy_Software/build/Drone_Autonomy_Software"
fi

# Check if the executable exists
if [ ! -f "$executable_path" ]; then
  echo "Executable not found or hasn't been compiled yet."
  exit 1
fi

# Get the directory of the script
script_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

# Attempt to copy the suppressions files from OpenCV install to project directory.
cp /usr/local/share/opencv*/*.supp $script_dir

# Find all .supp files in the same directory as the script
supp_files=$(find "$script_dir" -maxdepth 1 -type f -name "*.supp")

# Construct the Valgrind command
valgrind_cmd="valgrind -s --leak-check=yes --show-leak-kinds=all "
if [ "$1" = "GitHub-Action" ]; then
  valgrind_cmd+=" --log-file=/opt/Drone_Autonomy_Software/tools/valgrind/valgrind.rpt"
fi
for supp_file in $supp_files; do
  valgrind_cmd+=" --suppressions=$supp_file"
done
valgrind_cmd+=" $executable_path"

# Run the Valgrind command
eval $valgrind_cmd
