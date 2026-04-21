# -----------------------------------------------------------------------------
# Microsoft Azure Container Registry / .NET Microservices Template
# Project:      Hardware-Aware Case Conversion Engine
# Component:    Polyglot Build Orchestration (C++17 + .NET 8.0)
# Documentation: https://github.com/nitishhsinghhh/case-conversion-api
# -----------------------------------------------------------------------------
# VERSION HISTORY
# Version | Date       | Author       | Description
# --------|------------|--------------|----------------------------------------
# 1.0.0   | 2026-04-21 | Nitish Singh | Initial Release. Polyglot O11y integrated.
# 1.0.1   | 2026-04-22 | Nitish Singh | Fixed CMake source paths for Docker context.
# -----------------------------------------------------------------------------
# ARCHITECTURAL STRATEGY:
# * Multi-Stage Isolation: Segregates build-time dependencies (CMake) from runtime.
# * ABI Integrity: Compiles native shared objects (.so) within target SDK.
# * Artifact Promotion: Manual injection of native binaries into .NET publish root.
# -----------------------------------------------------------------------------

# --- STAGE 1: BUILD ---
FROM mcr.microsoft.com/dotnet/sdk:8.0 AS build

# Install native compilation toolchain (C++17/CMake)
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /src

# Copy solution context (Assuming context is the 'backend' directory)
COPY . .

# 1. Clean cache to enforce build reproducibility
# Paths adjusted: Removing 'CaseConversionAPI/' prefix as we are inside the context
RUN rm -rf CppLib/build

# 2. Build Native C++ Engine (Strategy/Factory Patterns)
RUN cmake -S CppLib -B CppLib/build -DCMAKE_BUILD_TYPE=Release
RUN cmake --build CppLib/build --parallel

# 3. Publish Managed .NET API (Kestrel/OTel)
RUN dotnet publish DotNetAPI -c Release -o /app/publish

# 4. ABI Bridge: Promote native artifact to managed output directory
# Note: Linux build produces .so (Shared Object) for the Debian-based SDK image
RUN cp CppLib/build/libProcessStringDLL.so /app/publish/

# --- STAGE 2: RUNTIME ---
FROM mcr.microsoft.com/dotnet/aspnet:8.0 AS runtime
WORKDIR /app

# Import optimized artifacts from build context
COPY --from=build /app/publish .

# System Configuration
EXPOSE 8080

# Entrypoint utilizes P/Invoke to bridge Managed and Unmanaged boundaries
ENTRYPOINT ["dotnet", "DotNetAPI.dll"]