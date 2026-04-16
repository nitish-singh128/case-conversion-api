# ---------- Build C++ ----------
# Use the official .NET SDK image as the build environment
# This stage compiles the C++ shared library and publishes the .NET API
# The resulting artifacts are then copied to the runtime image in the next stage
# The build stage includes the necessary tools to compile C++ code and build the .NET application
# The final runtime image is based on the ASP.NET image, which is optimized for running .NET applications
# The build stage ensures that all dependencies are resolved and the application is built in a clean environment
# The build stage also includes a step to clean any old CMake cache to ensure a fresh build of the C++ library
# The build stage compiles the C++ shared library using CMake and then publishes the .NET API to a specified output directory

# ==========================================
# STAGE 1: Compilation Environment
# ==========================================
FROM mcr.microsoft.com/dotnet/sdk:8.0 AS build

# Install C++ build tools
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /src

# Copy the entire monorepo context
# This is necessary because your C++ tests might reference folders 
# outside the immediate CppLib directory.
COPY . .

# DEBUG STEP: This will print the file structure in your GitHub logs 
# so you can verify exactly where the files are if it fails again.
RUN ls -R /src/backend/CaseConversionAPI

# 1. Clean old CMake cache
# Using the full path from the root context (.)
RUN rm -rf backend/CaseConversionAPI/CppLib/build

# 2. Build C++ shared library
# Ensure the case matches your GitHub folders (e.g., CppLib vs cpplib)
RUN cmake -S backend/CaseConversionAPI/CppLib \
          -B backend/CaseConversionAPI/CppLib/build \
          -DCMAKE_BUILD_TYPE=Release

RUN cmake --build backend/CaseConversionAPI/CppLib/build --parallel

# 3. Publish .NET API
# This assumes your .csproj is inside the DotNetAPI folder
RUN dotnet publish backend/CaseConversionAPI/DotNetAPI -c Release -o /app/publish

# 4. Copy shared library to the publish folder
# On Linux, CMake produces a .so file. 
# We copy it so the .NET runtime can find it via P/Invoke.
RUN cp backend/CaseConversionAPI/CppLib/build/libProcessStringDLL.so /app/publish/

# ==========================================
# STAGE 2: Optimized Runtime Image
# ==========================================
FROM mcr.microsoft.com/dotnet/aspnet:8.0
WORKDIR /app

# Copy only the compiled artifacts from the build stage
COPY --from=build /app/publish .

# Expose the default ASP.NET port
EXPOSE 8080

# Start the API
# Ensure "DotNetAPI.dll" matches your actual assembly name
ENTRYPOINT ["dotnet", "DotNetAPI.dll"]