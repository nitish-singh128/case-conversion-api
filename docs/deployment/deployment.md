# Deployment & Infrastructure Guide

This document defines the containerization, orchestration, and environment promotion strategy for the Case Conversion system.

---

## Table of Contents

- [Overview](#overview)
- [Docker Architecture](#docker-architecture)
  - [Multi-Stage Build (Backend)](#multi-stage-build-backend)
  - [Frontend UI (Nginx)](#frontend-ui-react--vite--nginx)
- [Environment Strategy](#environment-strategy)
- [Pipeline Execution](#pipeline-execution)
  - [Development](#development-environment)
  - [Staging (Promotion)](#staging-environment)
  - [Production](#production-environment)
- [Troubleshooting & Lessons Learned](#troubleshooting--lessons-learned)
- [Internal Architecture](#internal-architecture)

---

## Overview

The system is containerized using Docker and orchestrated via Docker Compose. It follows a **single-artifact promotion model**, ensuring consistency across environments.

Deployment Flow:

```bash
Development → Staging → Production
```

- Build Once: Images are built only during the Development/CI stage.
- Promote Forward: The same immutable image is re-tagged and moved through the pipeline.
- No Rebuilds: Eliminates "it worked on my machine" bugs by ensuring the exact same binary runs in Prod as in Staging.

---

## Docker Architecture

### Multi-Stage Build (Backend)

The backend utilizes a multi-stage build to ensure the final production image is lightweight and secure, containing only the runtime and the compiled binaries.

```Bash
# ---------- Stage 1: Build ----------
FROM mcr.microsoft.com/dotnet/sdk:8.0 AS build

# Install C++ toolchain
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake

WORKDIR /src
COPY . .

# Clean and build C++ shared library
RUN rm -rf CaseConversionAPI/CppLib/build && \
    cmake -S CaseConversionAPI/CppLib -B CaseConversionAPI/CppLib/build -DCMAKE_BUILD_TYPE=Release && \
    cmake --build CaseConversionAPI/CppLib/build --parallel

# Publish .NET API
RUN dotnet publish CaseConversionAPI/DotNetAPI -c Release -o /app/publish

# Copy compiled C++ binary to the publish folder
RUN cp CaseConversionAPI/CppLib/build/lib/libProcessStringDLL.so /app/publish/

# ---------- Stage 2: Runtime ----------
FROM mcr.microsoft.com/dotnet/aspnet:8.0
WORKDIR /app
COPY --from=build /app/publish .

EXPOSE 8080
ENTRYPOINT ["dotnet", "DotNetAPI.dll"]
```

### Frontend UI (React + Vite + Nginx)

In Production/Staging, the frontend is served via Nginx for high performance. In Development, it uses the Vite Dev Server for hot-module replacement (HMR).

- Production Port: 80 (Standard HTTP)

- Tech Stack: React 18, TypeScript, Vite.

- Static Hosting: Nginx handles routing and serves the minified JS/CSS bundle.

---

## Environment Strategy

Container images are tagged based on the stage of the pipeline.

| Environment | Tag      | Port (UI) | Port (API) | Purpose                          |
|------------|----------|-----------|------------|----------------------------------|
| Dev        | dev      | 5173      | 8080       | Active development & hot-reload  |
| Staging    | staging  | 5174      | 8081       | Pre-prod validation & QA         |
| Production | latest   | 80        | 8080       | Production deployment            |

```Bash
nitishhsinghhh/case-api:dev
nitishhsinghhh/case-api:staging
nitishhsinghhh/case-api:latest
```
---

## Pipeline Execution

### Development Environment

Used for active development and debiugging

```Bash
docker compose -f docker-compose.dev.yml up --build
```

Features:

- Local image build
- ASPNETCORE_ENVIRONMENT=Development
- Hot reload for frontend
- Debug logging enabled

### Staging Environment

Used for production-like validation.

#### Promote & Deploy Image: Staging

```Bash
# Tag and Push
docker tag nitishhsinghhh/case-api:dev nitishhsinghhh/case-api:staging
docker push nitishhsinghhh/case-api:staging

# Deploy Staging
docker compose -f docker-compose.staging.yml up -d
```

Features:

- Uses pre-built image
- ASPNETCORE_ENVIRONMENT=Staging
- No local builds
- Mirrors production behavior

--

### Production Environment

Used for final deployment.

#### Promote & Deploy Image: Prod

```Bash
# Tag and Push
docker tag nitishhsinghhh/case-api:staging nitishhsinghhh/case-api:latest
docker push nitishhsinghhh/case-api:latest

# Deploy Production
docker compose -f docker-compose.prod.yml up -d
```

Features:

- Stable image (latest)
- ASPNETCORE_ENVIRONMENT=Production
- Restart policies enabled
- Health checks enabled

--

## Troubleshooting & Lessons Learned

During the initial infrastructure setup, the following critical points were identified:

- Lean Runtime Images: The .NET 8 ASP.NET runtime image does not include curl. Avoid using curl in Docker Healthchecks unless you manually install it. Use TCP port checks or internal .NET probes instead.

- Empty Config Files: .NET will crash on startup if appsettings.Staging.json or appsettings.Production.json exists but is empty. Ensure these files contain valid JSON {} or are deleted if not needed.

- Port Conflicts: When running multiple environments on one host (MacBook), ensure ports (8080, 8081, 80) do not overlap across active containers.

- Zsh Comments: When copy-pasting commands from this guide into Zsh, avoid pasting lines starting with # as they may trigger "command not found" errors depending on shell configuration.

## Internal Architecture

```Bash
[ Browser ]  ←── (HTTP/JSON) ──→  [ Nginx Container (Frontend) ]
                                          │
                                   (Internal Network)
                                          │
                                          ▼
[ .NET 8 API Container (Backend) ] ←── (P/Invoke) ──→ [ C++ Shared Library ]
          │                                                    │
     (Controller)                                      (Strategy Pattern)
```

--

## Deployment & Environments

This project follows a containerized deployment workflow using Docker. Ensure you are authenticated with Docker Hub before pushing images.

1. Authentication

If your session has expired or you are on a new device, authenticate via the Docker CLI:

```Bash
docker login
```

Follow the on-screen instructions to enter your device activation code at login.docker.com/activate.

2. Promoting Images (Dev to Staging) then do Verification

After pushing, verify the image exists in the registry:

- Log in to Docker Hub.

- Navigate to the nitishhsinghhh/case-api repository.

- Check the Tags tab for the staging identifier.

--

## Key Principles

- Single artifact promotion (same image across environments)
- No rebuilds after development
- Environment isolation via configuration
- Consistent runtime behavior across all stages

--

## Summary

Summary
This deployment model ensures deterministic builds and consistent environments. By separating the heavy build-time dependencies (SDKs, C++ compilers) from the runtime, we maintain a secure, production-grade CI/CD readiness.
