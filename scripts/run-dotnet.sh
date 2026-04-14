#!/bin/bash
# run-dotnet.sh - Restore, build, publish, run .NET API

# Exit immediately if any command fails
set -e



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
# 4. Publish the project (optional)
# -------------------------------
echo
echo "===== Publishing project ====="
# Output folder: ../publish
dotnet publish -c Release -o ../publish

# -------------------------------
# 5. Run the API (optional)
# -------------------------------
echo
echo "===== Running API ====="
dotnet run -c Release

# -------------------------------
# 6. Back to project root
# -------------------------------
cd ../..