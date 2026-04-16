#!/bin/bash
#*********************************************************************/
#  Utility Script - .NET API Orchestration (Monorepo)                */
#                                                                    */
# Purpose   : Manages the lifecycle (Restore, Build, Publish, Run)   */
#              of the .NET 8 REST API within the monorepo context.   */
# Usage     : ./run-dotnet.sh                                        */
# Shell     : Bash (Targeted for Linux/macOS)                        */
#                                                                    */
# Notes     : - Dynamically resolves paths relative to script loc.   */
#             - Outputs build artifacts to /publish at root.         */
#                                                                    */
# Revision History:                                                  */
# ------------------------------------------------------------------ */
# Version    Date        Author          Description                 */
# ------------------------------------------------------------------ */
# 1.0        2026-04-14  Nitish Singh    Initial .NET build script   */
# 1.1        2026-04-15  Nitish Singh    Added Dynamic Path Logic    */
# 1.2        2026-04-16  Nitish Singh    Refactored exit/root logic  */
#*********************************************************************/

# Exit immediately if any command fails
set -e

# -------------------------------
# 1. Path Synchronization
# -------------------------------
# Get the directory where THIS script is located
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

# Navigate to the API project folder relative to this script
cd "$SCRIPT_DIR/../DotNetAPI"

echo "===== Context: Switched to $(pwd) ====="

# -------------------------------
# 2. Restore dependencies
# -------------------------------
echo "===== Restoring dependencies ====="
dotnet restore

# -------------------------------
# 3. Build the project
# -------------------------------
echo
echo "===== Building project ====="
dotnet build -c Release

# -------------------------------
# 4. Publish the project
# -------------------------------
echo
echo "===== Publishing project ====="
# Output to a 'publish' folder at the very root of the monorepo
dotnet publish -c Release -o ../../../publish

# -------------------------------
# 5. Run the API
# -------------------------------
echo
echo "===== Running API ====="
echo "===== API is LIVE. Press Ctrl+C to stop and return to root ====="

# This command blocks the script here until you stop the server
dotnet run -c Release --no-build

# -------------------------------
# 6. Return to Monorepo Root
# -------------------------------
# This only executes AFTER you press Ctrl+C
cd "$SCRIPT_DIR/../../.."
echo
echo "===== Completed. Back in project root: $(pwd) ====="