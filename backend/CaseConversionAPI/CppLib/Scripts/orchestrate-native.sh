#!/bin/bash
#*********************************************************************/
#  Utility Script - C++ Core Orchestration (Monorepo)                */
#                                                                    */
# Purpose   : Configures, builds, and executes C++ logic & tests.    */
# Location  : backend/CaseConversionAPI/CppLib/Scripts/run.sh        */
#                                                                    */
# Revision History:                                                  */
# ------------------------------------------------------------------ */
# Version    Date        Author          Description                 */
# ------------------------------------------------------------------ */
# 1.0        2026-04-14  Nitish Singh    Initial C++ Run Script      */
# 1.1        2026-04-15  Nitish Singh    Updated for /backend path   */
# 1.2        2026-04-16  Nitish Singh    Added Dynamic Path Sync     */
#*********************************************************************/

set -e

# -------------------------------
# 1. Path Synchronization
# -------------------------------
# Get the absolute path to this script's folder
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

# Target the CppLib root (one level up from Scripts/)
CPP_ROOT="$SCRIPT_DIR/.."
cd "$CPP_ROOT"

# -------------------------------
# 2. Compilation Layer
# -------------------------------
echo "===== Configuring & Building C++ Core ====="

# Create build directory relative to CppLib root
mkdir -p build
cd build

# Configure and Build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release --parallel

# -------------------------------
# 3. Execution Layer
# -------------------------------
echo -e "\n===== Running Core Tests ====="
# This is the primary validation for your C++ logic
./runTests

# -------------------------------
# 4. Workspace Restoration
# -------------------------------
# Return to the monorepo root
cd ../../../..

echo -e "\n===== Completed. Back in project root: $(pwd) ====="