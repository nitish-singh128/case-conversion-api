#!/bin/bash
# backend/CaseConversionAPI/DotNetAPI/run-dotnet.sh
# Restore, build, publish, run .NET API

# Exit immediately if any command fails
set -e

# -------------------------------
# 1. Project Directory Context
# -------------------------------
# We are currently in backend/CaseConversionAPI/DotNetAPI/

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
# Output folder: ../../../publish (moved up to the root)
dotnet publish -c Release -o ../../../publish

# -------------------------------
# 5. Run the API
# -------------------------------
echo
echo "===== Running API ====="
dotnet run -c Release

# -------------------------------
# 6. Back to project root
# -------------------------------
# Old: cd ../.. (This only went back to 'backend/')
# New: cd ../../.. (This goes back to 'word-case-api/')
cd ../../..
echo "===== Back in project root: $(pwd) ====="