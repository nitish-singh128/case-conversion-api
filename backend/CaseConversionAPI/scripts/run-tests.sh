#!/bin/bash
#*********************************************************************/
#  Utility Script - .NET Test Orchestration (Monorepo)               */
#                                                                    */
# Purpose   : Executes the .NET 8 Test Suite from the scripts folder.*/
# Usage     : ./run-tests.sh                                         */
#                                                                    */
# Revision History:                                                  */
# ------------------------------------------------------------------ */
# Version    Date        Author          Description                 */
# ------------------------------------------------------------------ */
# 1.0        2026-04-16  Nitish Singh    Initial Test Script         */
#*********************************************************************/

set -e

# -----------------------------------------------------------------
# 1. Path Synchronization
# -----------------------------------------------------------------
# Get the directory where THIS script is located
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

# To go "one level before tests":
# 1. From 'scripts/' to 'CaseConversionAPI/' (cd ..)
# 2. From 'CaseConversionAPI/' to 'backend/' (cd ..)
# This lands you where the 'tests/' folder is visible as a sibling
cd "$SCRIPT_DIR/.."

echo "===== Context: Switched to $(pwd) ====="

# -----------------------------------------------------------------
# 2. Execution
# -----------------------------------------------------------------
echo "===== Running .NET Tests ====="

# Path: backend/CaseConversionAPI/tests/DotNetTests/...
dotnet test tests/DotNetTests/DotNetAPI.Tests.csproj -c Release -v normal

echo "===== Tests completed ====="

# -----------------------------------------------------------------
# 3. Return to Project Root
# -----------------------------------------------------------------
cd "$SCRIPT_DIR/../../.."
echo "===== Script Finished at Root: $(pwd) ====="
echo "===== Returning control to your terminal... ====="