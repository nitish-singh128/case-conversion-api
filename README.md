# Case Conversion API

This project showcases a full-stack architecture in which a native C++ string processing engine is integrated with a .NET REST API and delivered through a modern frontend interface. It follows production-grade deployment practices, including environment isolation and structured artifact promotion. Overall, it serves as a rapid prototype highlighting system design and cross-language interoperability.

---

## Components

### 1. C++ Conversion Engine

- Implements multiple string conversion strategies (Alternating Case, Capitalize Words, Snake Case, etc.).
- Built as a shared library using **CMake**:
  - Windows → `libProcessStringDLL.dll`
  - macOS → `libProcessStringDLL.dylib`
  - Linux → `libProcessStringDLL.so`

### 2. .NET REST API Wrapper

- Uses **P/Invoke** to call the exported C++ DLL functions.
- Provides REST endpoints (e.g., `/api/WordCase/convert`) for frontend consumption.
- Built and published with `dotnet publish`.

### 3. Frontend UI (Vite + React/TypeScript)

- Provides a user interface to input text and select conversion type.
- Calls the .NET REST API endpoints to perform conversions.
- Built with `npm run build` → outputs static files in `dist/`.

---

## Build Pipeline

The project is designed to be built in sequence:

1.Build C++ DLL

```bash
mkdir -p CaseConversionAPI/CppLib/build
cd CaseConversionAPI/CppLib/build
cmake ..
cmake --build . --config Release

```

2.Build .NET API

```Bash
dotnet restore CaseConversionAPI/DotNetAPI
dotnet publish CaseConversionAPI/DotNetAPI -c Release -o ./publish
cp CaseConversionAPI/CppLib/build/libProcessString.* ./publish/
```

3.Build Frontend

```Bash
cd string-conversion-ui
npm install
npm run build
```

## C++ DLL Interop (ProcessStringDLL)

The project exposes a **C++ string conversion engine** to the .NET REST API using a DLL and P/Invoke.

## Purpose

`ProcessStringDLL.cpp` acts as a bridge between:

- C++ conversion logic
- C# service layer
- REST API controller

It dispatches user input to the appropriate conversion strategy using **Factory + Strategy pattern**.

### Exported Function

```cpp
extern "C" PROCESSSTRING_API const char* processStringDLL(const char* input, int choice);
```

### Parameters

- `input` → C-string input text
- `choice` → integer representing conversion type

### Returns

- Converted string (C-style pointer)
- Returns original input if invalid choice

### Supported Conversion Choices

| Choice | Conversion       |
| ------ | ---------------- |
| 1      | Alternating Case |
| 2      | Capitalize Words |
| 3      | Lower Case       |
| 4      | Upper Case       |
| 5      | Sentence Case    |
| 6      | Toggle Case      |
| 7      | Reverse          |
| 8      | Remove Vowels    |
| 9      | Remove Spaces    |
| 10     | Invert Words     |
| 11     | Snake Case       |
| 12     | Kebab Case       |
| 13     | Leet Speak       |

### Design Patterns Used

- Strategy Pattern
- Factory Pattern
- Client Dispatcher

### Flow

```Bash
REST API (C#)
     ↓
ProcessStringService (P/Invoke)
     ↓
processStringDLL (C++)
     ↓
Factory → Strategy → Client
     ↓
Converted String
```

### Build Output

The C++ project builds a shared library:

- Windows → `libProcessStringDLL.dll`
- macOS → `libProcessStringDLL.dylib`
- Linux → `libProcessStringDLL.so`

This library is loaded by the C# service using P/Invoke.

### Integration Layer (C#)

The .NET service calls the DLL:

```csharp
[DllImport("libProcessStringDLL")]
private static extern IntPtr processStringDLL(string input, int choice);
```

This enables the REST API to use native C++ performance-critical logic.

## Testing Strategy

### 1. Core Testing (C++)

- Google Test framework
- Validates:
  - Strategy implementations
  - Factory logic

### 2. DLL Integration Testing

- Tests exported function `processStringDLL`
- Ensures:
  - Correct interop behavior
  - Memory safety
  - End-to-end conversion

### 3. CI Testing

- Executed via GitHub Actions
- Cross-platform validation (Windows, macOS, Linux)

## Automated Testing (xUnit + ASP.NET Core Integration Tests)

This project uses xUnit for automated testing of the .NET REST API.

What is being tested?
The tests validate the full API flow:

- ✔ HTTP request → API endpoint
- ✔ DTO model binding (JSON input)
- ✔ Business logic execution
- ✔ Response validation

### Test Architecture

```Bash
      xUnit Test Runner
            ↓
      HttpClient (WebApplicationFactory)
            ↓
      In-Memory ASP.NET Core API
            ↓
      Controller / Minimal API Endpoint
            ↓
      C# Business Logic Execution
            ↓
      Response Validation
```

### Architecture Overview

```Bash
C++ Conversion Engine
        ↑
   DLL Export Layer
        ↑
C# P/Invoke Wrapper
        ↑
ProcessStringService
        ↑
WordCaseController
        ↑
REST API
```

## Architecture View

```Bash
                +---------------------+
                |   Frontend (React)  |
                |   Vite + TypeScript |
                +----------+----------+
                           |
                       REST API call
                           |
                +----------v----------+
                |   REST API (C#)     |
                |   WordCaseController|
                +----------+----------+
                           |
                       P/Invoke
                           |
                +----------v----------+
                |  ProcessStringDLL   |  <-- DLL wrapper
                +----------+----------+
                           |
                +----------v----------+
                |   Core C++ Logic    |
                | (Factory + Strategy)|
                +----------+----------+
                           |
         +-----------------+-----------------+
         |                                   |
+--------v--------+               +----------v----------------+
|  main.cpp CLI   |               | Google Tests (Core Logic) |
|  Local testing  |               | Unit testing              |
+-----------------+               +---------------------------+
                           |
                +----------v----------+
                |  xUnit Tests        |
                | (API Integration)   |
                | HttpClient + API    |
                | In-memory host      |
                +---------------------+
         
```

## Tech Stack

- C++ (conversion logic, built with CMake)
- .NET 8 (REST API wrapper, P/Invoke)
- React + Vite + TypeScript (frontend UI)
- GitHub Actions (CI/CD pipeline)
- Azure App Service + GitHub Pages (deployment targets)

## Run Backend using Docker

1. Create Dockerfile (Project Root)

```Bash
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

2.Start Docker Desktop

Make sure Docker Desktop is running. You can use commmand in terminal to start the ddocker

```Bash
open -a Docker
```

3.Build Docker image

From the project root (where the Dockerfile exists):

```Bash
docker build -t case-conversion-api .
```

4.Run container

```Bash
docker run -p 8080:8080 case-conversion-api
```

You should see:

```Bash
Now listening on: http://[::]:8080
```

5.Open Swagger UI
Open in browser:

```Bash
http://localhost:8080/
```

## Running Full Stack using Docker Compose

To run Frontend + Backend together, use Docker Compose.

1.Update Frontend API URL

ENsure the react frontned calls:

```Bash
http://localhost:8080/api/WordCase/convert
```

2.Create docker-compose.yml (Project Root)

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

3.Run Full Stack

```Bash
docker compose up --build
```

This will start:

- Backend → http://localhost:8080
- Frontend → http://localhost:5173

## Environment-Based Deployment (Dev → Staging → Prod)

This project supports multi-environment deployment using Docker Compose and image promotion.

### Deployment Strategy

The system follows

```Bash
Development → Staging → Production
```

- Build once in dev
- Promote the same Docker image forward
- Avoid rebuilding for each environment

### Docker Image Tagging Strategy

| Environment | Tag       |
| ----------- | --------- |
| Dev         | `dev`     |
| Staging     | `staging` |
| Production  | `latest`  |

```Bash
nitishhsinghhh/case-api:dev
nitishhsinghhh/case-api:staging
nitishhsinghhh/case-api:latest
```

## Development Environment

Used for local development with hot reload and debugging.

Run Dev

```Bash
docker compose -f docker-compose.dev.yml up --build
```

Features

- Builds image locally
- Uses ASPNETCORE_ENVIRONMENT=Development
- Frontend runs with npm run dev
- Debug logs enabled

## Staging Environment

Used for production-like validation before release

Promote Image from Dev

```Bash
docker tag nitishhsinghhh/case-api:dev nitishhsinghhh/case-api:staging
docker push nitishhsinghhh/case-api:staging
```

Run Staging

```Bash
docker compose -f docker-compose.staging.yml up -d
```

Features

- Uses pre-built Docker image
- Uses ASPNETCORE_ENVIRONMENT=Staging
- No local builds
- Simulates production behavior

## Production Environment

Used for final deployment.

Promote Image from Staging

```Bash
docker tag nitishhsinghhh/case-api:staging nitishhsinghhh/case-api:latest
docker push nitishhsinghhh/case-api:latest
```

Run Production

```Bash
docker compose -f docker-compose.prod.yml up -d
```

Features

- Uses stable image (latest)
- Uses ASPNETCORE_ENVIRONMENT=Production
- Restart policies enabled
- Health checks enabled

## Full deployment flow

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

## Docker compose file

| File                         | Purpose                |
| ---------------------------- | ---------------------- |
| `docker-compose.dev.yml`     | Local development      |
| `docker-compose.staging.yml` | Pre-production testing |
| `docker-compose.prod.yml`    | Production deployment  |

## Key Principles

- Single artifact promotion (same image across environments)
- Environment-specific configuration via ASPNETCORE_ENVIRONMENT
- No rebuilds after dev
- Isolation of environments

## Resulting Architecture

```Bash
Developer → Dev Build → Docker Image
                        ↓
                    Staging
                        ↓
                    Production
```

## Architecture (Containerized)

```Bash
                +---------------------+
                |   Frontend (React)  |
                |   Vite + TypeScript |
                |   (Docker)          |
                +----------+----------+
                           |
                       HTTP (REST)
                           |
                +----------v----------+
                |   .NET REST API     |
                |   ASP.NET Core      |
                |   (Docker)          |
                +----------+----------+
                           |
                        P/Invoke
                           |
                +----------v----------+
                |  C++ Shared Library |
                |  libProcessStringDLL   |
                +----------+----------+
                           |
                +----------v----------+
                | Factory + Strategy  |
                |  Conversion Engine  |
                +---------------------+
```

## Deployment Architecture (Docker Compose)

```Bash
+-------------------+        +-------------------+
|   Frontend        | -----> |   Backend API     |
|   React + Vite    |        |   .NET + C++ DLL  |
|   Port 5173       |        |   Port 8080       |
+-------------------+        +-------------------+
```

## Runtime Flow

```Bash
         Browser
            ↓
         React UI (Docker)
            ↓
         HTTP REST Call
            ↓
         ASP.NET Core API (Docker)
            ↓
         P/Invoke
            ↓
         C++ Shared Library
            ↓
         Strategy Pattern Conversion
            ↓
         Response back to UI

```
