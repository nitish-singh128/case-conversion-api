#!/bin/bash
#*********************************************************************/
#  Utility Script - Frontend Workspace Initialization                */
#                                                                    */
# Purpose   : Scaffolds the directory structure for the Vite/TS UI.   */
# Location  : scripts/init-frontend.sh                               */
#                                                                    */
# Revision History:                                                  */
# ------------------------------------------------------------------ */
# Version    Date        Author          Description                 */
# ------------------------------------------------------------------ */
# 1.0        2026-04-16  Nitish Singh    Initial Scaffold Script     */
#*********************************************************************/

set -e

# Root folder
PROJECT_NAME="string-conversion-ui"

echo "===== Initializing Frontend: $PROJECT_NAME ====="

# Create Directory Hierarchy
echo "Creating project structure..."
mkdir -p $PROJECT_NAME/src/api
mkdir -p $PROJECT_NAME/src/ui
mkdir -p $PROJECT_NAME/src/types

# Initialize Core Files
touch $PROJECT_NAME/src/api/wordCaseApi.ts
touch $PROJECT_NAME/src/ui/converter.ts
touch $PROJECT_NAME/src/types/models.ts
touch $PROJECT_NAME/src/main.ts
touch $PROJECT_NAME/src/style.css

# Initialize Config Files
touch $PROJECT_NAME/index.html
touch $PROJECT_NAME/package.json
touch $PROJECT_NAME/tsconfig.json
touch $PROJECT_NAME/vite.config.ts

echo "Project structure created successfully!"
echo "Location: $(pwd)/$PROJECT_NAME"