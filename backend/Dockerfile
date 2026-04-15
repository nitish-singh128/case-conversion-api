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
COPY . .

# Clean old CMake cache
RUN rm -rf CaseConversionAPI/CppLib/build

# Build C++ shared library
RUN cmake -S CaseConversionAPI/CppLib -B CaseConversionAPI/CppLib/build -DCMAKE_BUILD_TYPE=Release
RUN cmake --build CaseConversionAPI/CppLib/build --parallel

# Publish .NET API
RUN dotnet publish CaseConversionAPI/DotNetAPI -c Release -o /app/publish

# Copy shared library
RUN cp CaseConversionAPI/CppLib/build/lib/libProcessStringDLL.so /app/publish/

# ---------- Runtime ----------
FROM mcr.microsoft.com/dotnet/aspnet:8.0

WORKDIR /app
COPY --from=build /app/publish .

EXPOSE 8080

ENTRYPOINT ["dotnet", "DotNetAPI.dll"]