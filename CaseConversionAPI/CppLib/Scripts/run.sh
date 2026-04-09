#!/bin/bash
# run.sh - Build, run app, and tests

# Exit on any error
set -e

# Create build directory if it doesn't exist
mkdir -p build
cd build

# Configure project with CMake
cmake ..

# Build everything
cmake --build . --config Release

echo
echo "===== Running Tests ====="
./runTests

echo
echo "===== Running App ====="
./app

# Back to project root
cd ..