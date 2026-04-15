#!/bin/bash
# backend/CaseConversionAPI/CppLib/run.sh
# Build, run app, and tests

# Revision History:
# 1.0  2026-04-14  Initial C++ Run Script
# 1.1  2026-04-15  Updated for /backend monorepo structure

# Exit on any error
set -e

# -------------------------------
# 1. Compilation Layer
# -------------------------------
# Create build directory if it doesn't exist
mkdir -p build
cd build

# Configure project with CMake
cmake ..

# Build everything
cmake --build . --config Release

# -------------------------------
# 2. Execution Layer
# -------------------------------
echo
echo "===== Running Tests ====="
./runTests

echo
echo "===== Running App ====="
./app

# -------------------------------
# 3. Workspace Restoration
# -------------------------------
# Old: cd .. (This only went back to CppLib/)
# New: cd ../../.. (CppLib -> CaseConversionAPI -> backend -> root)
cd ../../..
echo "===== Back in project root: $(pwd) ====="