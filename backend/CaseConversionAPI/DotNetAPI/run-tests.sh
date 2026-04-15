#!/bin/bash
set -e

echo "===== Running .NET Tests ====="

dotnet test ../tests/DotNetTests/DotNetAPI.Tests.csproj -c Release -v normal

echo "===== Tests completed ====="