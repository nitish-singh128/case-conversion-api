# ---------- Build C++ ----------
# Use the official .NET SDK image as the build environment
# This stage compiles the C++ shared library and publishes the .NET API
# The resulting artifacts are then copied to the runtime image in the next stage
# The build stage includes the necessary tools to compile C++ code and build the .NET application
# The final runtime image is based on the ASP.NET image, which is optimized for running .NET applications
# The build stage ensures that all dependencies are resolved and the application is built in a clean environment
# The build stage also includes a step to clean any old CMake cache to ensure a fresh build of the C++ library
# The build stage compiles the C++ shared library using CMake and then publishes the .NET API to a specified output directory

FROM mcr.microsoft.com/dotnet/sdk:8.0 AS build

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake

WORKDIR /src
# Copy everything from the root context (which includes the 'backend' folder)
COPY . .

# 1. Clean old CMake cache (Updated path)
RUN rm -rf backend/CaseConversionAPI/CppLib/build

# 2. Build C++ shared library (Added 'backend/' prefix)
RUN cmake -S backend/CaseConversionAPI/CppLib -B backend/CaseConversionAPI/CppLib/build -DCMAKE_BUILD_TYPE=Release
RUN cmake --build backend/CaseConversionAPI/CppLib/build --parallel

# 3. Publish .NET API (Added 'backend/' prefix)
RUN dotnet publish backend/CaseConversionAPI/DotNetAPI -c Release -o /app/publish

# 4. Copy shared library (Note: check if your CMake output goes to 'lib' or root of build)
RUN cp backend/CaseConversionAPI/CppLib/build/libProcessStringDLL.so /app/publish/

# ---------- Runtime ----------
FROM mcr.microsoft.com/dotnet/aspnet:8.0

WORKDIR /app
COPY --from=build /app/publish .

EXPOSE 8080

# Ensure this matches the actual .csproj name in your backend folder
ENTRYPOINT ["dotnet", "CaseConversionAPI.dll"]