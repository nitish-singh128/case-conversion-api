#!/bin/bash
#*********************************************************************/
#  Utility Script - Database Scaffolding (Microsoft-Style)           */
#                                                                    */
# Purpose   : Generates the specialized database folder hierarchy    */
#             within the backend persistence layer.                  */
# Location  : backend/CaseConversionAPI/scripts/setup_structure.sh   */
#                                                                    */
# Revision History:                                                  */
# ------------------------------------------------------------------ */
# Version    Date        Author          Description                 */
# ------------------------------------------------------------------ */
# 1.0        2026-04-21  Nitish Singh    Initial DB Scaffolding      */
#*********************************************************************/

set -e

# Define the base backend path
BACKEND_PATH="../../database"

echo "==========================================================="
echo "Initializing Microsoft-Standard Database Structure..."
echo "Target Path: $BACKEND_PATH"
echo "==========================================================="

# Create the directories
# - tables: For DDL (Data Definition Language)
# - procedures: For DLP (Data Logic/Programmability)
# - scripts: For DML/Seed scripts (Data Manipulation)
mkdir -p "$BACKEND_PATH/tables"
mkdir -p "$BACKEND_PATH/procedures"
mkdir -p "$BACKEND_PATH/scripts"

echo "Structure created successfully for Project: CaseConversionAPI"
echo "-----------------------------------------------------------"
ls -R "$BACKEND_PATH"
echo "-----------------------------------------------------------"