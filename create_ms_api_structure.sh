#!/bin/bash
# Script to create Microsoft-style folder structure for CaseConversionAPI

ROOT="CaseConversionAPI"

echo "Creating Microsoft-style folder structure for CaseConversionAPI..."

# -----------------------------
# C++ library project
# -----------------------------
mkdir -p $ROOT/CppLib/include
mkdir -p $ROOT/CppLib/src

# -----------------------------
# .NET API project
# -----------------------------
mkdir -p $ROOT/DotNetAPI/Controllers
mkdir -p $ROOT/DotNetAPI/Models
mkdir -p $ROOT/DotNetAPI/Services

# Placeholder .NET files
touch $ROOT/DotNetAPI/Program.cs
touch $ROOT/DotNetAPI/Startup.cs
touch $ROOT/DotNetAPI/DotNetAPI.csproj
touch $ROOT/DotNetAPI/Controllers/WordCaseController.cs

# -----------------------------
# DLL output folder
# -----------------------------
mkdir -p $ROOT/lib

# -----------------------------
# Tests
# -----------------------------
mkdir -p $ROOT/tests/CppTests
mkdir -p $ROOT/tests/DotNetTests

# -----------------------------
# Scripts
# -----------------------------
mkdir -p $ROOT/scripts
touch $ROOT/scripts/create_structure.sh

# -----------------------------
# Root files
# -----------------------------
touch $ROOT/README.md
touch $ROOT/CMakeLists.txt

echo "Microsoft-style folder structure created under $ROOT!"