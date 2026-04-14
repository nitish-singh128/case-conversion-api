# Deployment & Infrastructure Guide

This document defines the containerization, orchestration, and environment promotion strategy for the Case Conversion system.

---

## Overview

The system is containerized using Docker and orchestrated via Docker Compose. It follows a **single-artifact promotion model**, ensuring consistency across environments.

Deployment Flow:

```bash
Development → Staging → Production
```

- Build once in Deployment
- Promote the same image formward
- No rebuils across environments

## Docker Architecture

### Multi-Stage Build (Backend)

```Bash
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
```

## Docker Compose (Full Stack)

```Bash
version: "3.9"

services:
  backend:
    build: .
    container_name: case-api
    ports:
      - "8080:8080"
    restart: unless-stopped

  frontend:
    image: node:20
    container_name: case-ui
    working_dir: /app
    volumes:
      - ./string-conversion-ui:/app
    ports:
      - "5173:5173"
    command: sh -c "npm install && npm run dev -- --host"
    depends_on:
      - backend
```

## Local Development

Run the full stack locally:

```Bash
docker compose up --build
```

Services:

- Backend → http://localhost:8080
- Frontend → http://localhost:5173

## Environment Strategy

The system supports three environments to ensure a smooth development, testing, and deployment lifecycle.

| Environment | Purpose                     |
|------------|-----------------------------|
| Dev        | Local development           |
| Staging    | Pre-production testing      |
| Production | Live deployment             |

## Image Tagging Strategy

Container images are tagged based on the deployment environment to ensure clear versioning and controlled releases.

| Environment | Tag     |
|------------|---------|
| Dev        | dev     |
| Staging    | staging |
| Production | latest  |

### Example

```Bash
nitishhsinghhh/case-api:dev
nitishhsinghhh/case-api:staging
nitishhsinghhh/case-api:latest
```

## Development Environment

Used for active development and debiugging

```Bash
docker compose -f docker-compose.dev.yml up --build
```

Features:

- Local image build
- ASPNETCORE_ENVIRONMENT=Development
- Hot reload for frontend
- Debug logging enabled

--

## Staging Environment

Used for production-like validation.

### Promote Image

```Bash
docker tag nitishhsinghhh/case-api:dev nitishhsinghhh/case-api:staging
docker push nitishhsinghhh/case-api:staging
```

### Run Staging

```Bash
docker compose -f docker-compose.staging.yml up -d
```

Features:

- Uses pre-built image
- ASPNETCORE_ENVIRONMENT=Staging
- No local builds
- Mirrors production behavior

--

## Production Environment

Used for final deployment.

### Promote Image

```Bash
docker tag nitishhsinghhh/case-api:staging nitishhsinghhh/case-api:latest
docker push nitishhsinghhh/case-api:latest
```

### Run Production

```Bash
docker compose -f docker-compose.prod.yml up -d
```

Features:

- Stable image (latest)
- ASPNETCORE_ENVIRONMENT=Production
- Restart policies enabled
- Health checks enabled

--

## Full Deployment Flow

```Bash
# Step 1: Build in Dev
docker compose -f docker-compose.dev.yml up --build -d
docker push nitishhsinghhh/case-api:dev

# Step 2: Promote to Staging
docker tag nitishhsinghhh/case-api:dev nitishhsinghhh/case-api:staging
docker push nitishhsinghhh/case-api:staging
docker compose -f docker-compose.staging.yml up -d

# Step 3: Promote to Production
docker tag nitishhsinghhh/case-api:staging nitishhsinghhh/case-api:latest
docker push nitishhsinghhh/case-api:latest
docker compose -f docker-compose.prod.yml up -d
```

## Key Principles

- Single artifact promotion (same image across environments)
- No rebuilds after development
- Environment isolation via configuration
- Consistent runtime behavior across all stages

## Architecture (Containerized)

```Bash
Frontend (React + Vite)
        ↓
REST API (.NET 8)
        ↓
P/Invoke Bridge
        ↓
C++ Shared Library
        ↓
Strategy + Factory Engine
```

## Summary

This deployment model ensures:

- Deterministic builds
- Consistent environments
- Scalable containerized execution
- Production-grade CI/CD readiness

The system adheres to modern DevOps best practices by separating build and runtime concerns while maintaining strict control over artifact promotion.
