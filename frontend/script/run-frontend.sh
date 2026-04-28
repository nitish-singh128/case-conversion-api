#!/bin/bash
#*********************************************************************/
#  Utility Script - Frontend Development Server                      */
#                                                                    */
# Revision History:                                                  */
# ------------------------------------------------------------------ */
# Version    Date        Author          Description                 */
# ------------------------------------------------------------------ */
# 1.0        2026-04-16  Nitish Singh    Initial Dev Runner          */
# 1.1        2026-04-16  Nitish Singh    Added Apple Silicon Fix     */
#*********************************************************************/

set -e

# Path Synchronization
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
FRONTEND_ROOT="$SCRIPT_DIR/.."
cd "$FRONTEND_ROOT"

echo "===== Starting Frontend Environment ====="

# If node_modules is missing OR if we want to ensure arm64 bindings
if [ ! -d "node_modules" ]; then
    echo "Installing arm64 native bindings for macOS..."
    npm install
fi

# Run Vite dev server
echo "Launching Vite server on port 5173..."
npx vite --port 5173 --open