![C++ CI + Test](https://img.shields.io/github/actions/workflow/status/nitishhsinghhh/case-conversion-api/cpp-ci.yml?branch=main&label=C%2B%2B%20Core&style=flat-square)
![.NET API Status](https://img.shields.io/github/actions/workflow/status/nitishhsinghhh/case-conversion-api/dotnet-api.yml?branch=main&label=.NET%20API&style=flat-square)
![.NET API Integeration Tests](https://img.shields.io/github/actions/workflow/status/nitishhsinghhh/case-conversion-api/dotnet-tests.yml?branch=main&label=Integeration%20Tests&style=flat-square)
![Full Project Build](https://img.shields.io/github/actions/workflow/status/nitishhsinghhh/case-conversion-api/cpp-ci-DLL-all.yml?branch=main&label=Full%20Stack%20Build&style=flat-square)
![Docker Push](https://img.shields.io/github/actions/workflow/status/nitishhsinghhh/case-conversion-api/docker-build.yml?branch=main&label=Docker%20Registry&style=flat-square)
![Deployment](https://img.shields.io/github/actions/workflow/status/nitishhsinghhh/case-conversion-api/deploy.yml?branch=main&label=Production%20Deploy&style=flat-square)
![Deployment](https://img.shields.io/github/actions/workflow/status/nitishhsinghhh/case-conversion-api/cpp-quality.yml?branch=main&label=CPP%20Code%20Quality&style=flat-square)

![C++](https://img.shields.io/badge/C++-17-blue.svg)
![.NET](https://img.shields.io/badge/.NET-8.0-purple.svg)
![React](https://img.shields.io/badge/React-2024-61DAFB.svg)
![Docker](https://img.shields.io/badge/Docker-Ready-2496ED.svg)
![CI/CD](https://img.shields.io/badge/Pipeline-Verified-green.svg)
![Telemetry](https://img.shields.io/badge/Telemetry-OpenTelemetry-orange.svg)

![Visitors](https://komarev.com/ghpvc/?username=nitishhsinghhh&repo=case-conversion-api&label=Repo%20Views&color=2088FF&style=flat-square)

---

# Polyglot String Conversion Engine & API

A high-performance system demonstrating a Native C++17 engine seamlessly integrated into a .NET 8 managed ecosystem. This project serves as a blueprint for handling manual memory management across the ABI boundary, implementing extensible Strategy patterns, and maintaining an immutable Docker promotion pipeline from development to production.

## System Architecture

This project is an exercise in Cross-Language Interoperability and Architectural Rigor. It solves the challenge of exposing high-performance, unmanaged C++ logic to a modern, managed web stack.

- The Core: A C++17 engine utilizing the Strategy and Factory patterns for extensible string processing.
- The Bridge: A custom C-style ABI wrapper with explicit memory ownership management (allocate/free contract).
- The Gateway: A .NET 8 REST API utilizing Dynamic P/Invoke via NativeLibrary for platform-agnostic service execution.
- The UI: A type-safe React/TypeScript frontend built on Vite for sub-second developer turnaround.
- The DevOps: A multi-stage Docker orchestration supporting Artifact Promotion (Dev → Staging → Prod) to ensure environmental parity.

![alt text](assets/image.png)

---

## Components

### 1. C++ Conversion Engine

- Implements multiple string conversion strategies.
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

1. Native Layer: Compile the C++ Shared Library.

```bash
mkdir -p CaseConversionAPI/CppLib/build
cd CaseConversionAPI/CppLib/build
cmake ..
cmake --build . --config Release

```

2.Managed Layer: Restore and Publish the .NET API, injecting the native .so/.dll into the publish artifact.

```Bash
dotnet restore CaseConversionAPI/DotNetAPI
dotnet publish CaseConversionAPI/DotNetAPI -c Release -o ./publish
cp CaseConversionAPI/CppLib/build/libProcessString.* ./publish/
```

3.Frontend Layer: Build the optimized static assets via Vite.

```Bash
cd string-conversion-ui
npm install
npm run build
```

---

### Integration Layer (C#)

The .NET service calls the DLL:

```csharp
// Updated for Production Grade Interop
[DllImport("libProcessStringDLL", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
private static extern IntPtr processStringDLL([MarshalAs(UnmanagedType.LPStr)] string input, int choice);
```

This enables the REST API to use native C++ performance-critical logic.

---

## Testing Strategy

- Native: GoogleTest suite for algorithmic validation.

- Managed: xUnit integration tests utilizing WebApplicationFactory.

- Stress: Validation of 5MB+ large object payloads across the language boundary.

- CI: GitHub Actions Matrix builds enforcing cross-platform parity on every push.

---

## Telemetry Infrastructure

A dedicated script manages the lifecycle of the OTLP (OpenTelemetry Protocol) backend:

```Bash
# Start the Jaeger collector and UI
./scripts/run-telemetry.sh start
```

- UI Dashboard: http://localhost:16686

- OTLP Endpoint: http://localhost:4317 (gRPC)

### Performance Metrics & Insights

- ABI Latency: Verification that data marshalling between System.String and char* remains under 1ms.

- Security Gate Logging: Native 5MB buffer violations are automatically tagged as Error status in the trace, allowing for instant debugging of failed payloads.

-Context Propagation: The W3C Trace ID is passed into the C++ engine, ensuring that native logs can be correlated back to specific API calls.

## Engineering Deep Dive

1. Concurrency & Thread-Safety

In a high-throughput REST environment, thread-safety is paramount. The integration layer has been engineered with the following principles:

- Stateless Execution: The native C++ engine is entirely Stateless. Every call to processStringDLL operates on its own stack and heap allocations, ensuring that the .NET ThreadPool can safely execute concurrent P/Invoke calls.

- Reentrancy: The library is fully reentrant. There are no global variables or shared static states within the conversion logic, eliminating the risk of race conditions or shared-state contention.

- Thread-Safe Marshalling: All data passed across the ABI boundary is deep-copied, ensuring that memory used by one thread is never modified by another.

2. Design Patterns Used (Expanded)

- Strategy Pattern: Encapsulates conversion algorithms, allowing for runtime algorithm selection.

- Factory Pattern: Decouples the client from the specific strategy implementation.

- Client Dispatcher: Manages the lifecycle of the strategy and handles the execution pipeline.

- RAII (Resource Acquisition Is Initialization): Employed in C++ to manage internal resources and in C# via IDisposable to ensure native library handles are released.

Note on Thread-Safety: The native C++ engine is designed to be Stateless and Thread-Safe, allowing the .NET pool to safely execute concurrent P/Invoke calls without shared-state contention.

---

## Running the System

```Bash
docker compose up --build
```

This will start:

- Backend → http://localhost:8080
- Frontend → http://localhost:5173

---

## Summary

Developed a cross-platform string conversion ecosystem utilizing a high-performance C++17 engine integrated into a .NET 8 microservice via P/Invoke. Engineered a Zero-Leak memory management policy across the ABI boundary and implemented a multi-stage Docker CI/CD pipeline supporting immutable artifact promotion across Dev, Staging, and Production environments.
