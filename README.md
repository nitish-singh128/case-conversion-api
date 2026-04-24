![C++ CI](https://img.shields.io/github/actions/workflow/status/nitishhsinghhh/case-conversion-api/native-engine-ci.yml?branch=main&label=Engine%3A%20Native&style=flat-square)
![.NET API Status](https://img.shields.io/github/actions/workflow/status/nitishhsinghhh/case-conversion-api/dotnet-tests.yml?branch=main&label=Gateway%3A%20.NET%208&style=flat-square)
![.NET API Integeration Tests](https://img.shields.io/github/actions/workflow/status/nitishhsinghhh/case-conversion-api/dotnet-integration-tests.yml?branch=main&label=Integeration%20Tests&style=flat-square)
![Full Project Build](https://img.shields.io/github/actions/workflow/status/nitishhsinghhh/case-conversion-api/native-engine-ci_DLL.yml?branch=main&label=Build%3A%20Multi-OS&style=flat-square)
![Docker Push](https://img.shields.io/github/actions/workflow/status/nitishhsinghhh/case-conversion-api/docker-hub-distribution.yml?branch=main&label=Registry%3A%20Image&style=flat-square)
![Deployment](https://img.shields.io/github/actions/workflow/status/nitishhsinghhh/case-conversion-api/production-release.yml?branch=main&label=Release%3A%20v2.0.0&style=flat-square)
![Quality](https://img.shields.io/github/actions/workflow/status/nitishhsinghhh/case-conversion-api/cpp-quality-guard.yml?branch=main&label=Quality%3A%20Clang&style=flat-square)
![Telemetry E2E](https://img.shields.io/github/actions/workflow/status/nitishhsinghhh/case-conversion-api/telemetry-e2e-verification.yml?branch=main&label=Observability%3A%20E2E&style=flat-square)
![Security Audit](https://img.shields.io/github/actions/workflow/status/nitishhsinghhh/case-conversion-api/security-analysis.yml?branch=main&label=Security%3A%20CodeQL&style=flat-square)

![C++](https://img.shields.io/badge/C++-17-blue.svg)
![.NET](https://img.shields.io/badge/.NET-8.0-purple.svg)
![React](https://img.shields.io/badge/React-2024-61DAFB.svg)
![Docker](https://img.shields.io/badge/Docker-Ready-2496ED.svg)
![CI/CD](https://img.shields.io/badge/Pipeline-Verified-green.svg)
![Telemetry](https://img.shields.io/badge/Telemetry-OpenTelemetry-orange.svg)
![License](https://img.shields.io/github/license/nitishhsinghhh/case-conversion-api?style=flat-square&color=blue)

![Visitors](https://komarev.com/ghpvc/?username=nitishhsinghhh&repo=case-conversion-api&label=Repo%20Views&color=2088FF&style=flat-square)

---

# The Hardware-Aware Polyglot String Conversion Engine & API

A high-performance system demonstrating a Native C++17 engine seamlessly integrated into a .NET 8 managed ecosystem. This project serves as a blueprint for handling manual memory management across the ABI boundary, implementing extensible Strategy patterns, and maintaining an immutable Docker promotion pipeline from development to production.

## System Architecture

This project addresses the challenges of exposing high-performance, unmanaged C++ logic to a modern, managed web stack with architectural rigor.

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

## Engineering Deep Dive

### 1. Concurrency & Thread-Safety

In a high-throughput REST environment, thread-safety is paramount. The integration layer has been engineered with the following principles:

- Stateless Execution: The native C++ engine is entirely Stateless. Every call to processStringDLL operates on its own stack and heap allocations, ensuring that the .NET ThreadPool can safely execute concurrent P/Invoke calls.

- Reentrancy: The library is fully reentrant. There are no global variables or shared static states within the conversion logic, eliminating the risk of race conditions or shared-state contention.

- Thread-Safe Marshalling: All data passed across the ABI boundary is deep-copied, ensuring that memory used by one thread is never modified by another.

### 2. Design Patterns Used

- Strategy Pattern: Encapsulates conversion algorithms, allowing for runtime algorithm selection.

- Factory Pattern: Decouples the client from the specific strategy implementation.

- Client Dispatcher: Manages the lifecycle of the strategy and handles the execution pipeline.

- RAII (Resource Acquisition Is Initialization): Employed in C++ to manage internal resources and in C# via IDisposable to ensure native library handles are released.

Note on Thread-Safety: The native C++ engine is designed to be Stateless and Thread-Safe, allowing the .NET pool to safely execute concurrent P/Invoke calls without shared-state contention.

### 3. Defensive Interop Design

- Sentinel Pattern: The C++ engine returns a sentinel string (`ERROR_BUFFER_OVERFLOW_LIMIT_5MB`) upon security violation. The C# layer traps this and re-throws a managed `ArgumentException`, providing a clean error path for the API consumer.
- Reentrant & Stateless: The native engine maintains no global state. Every P/Invoke call operates on its own stack and heap allocation, ensuring full reentrancy for parallel execution.
- Zero-Footprint Disposal: Implements a strict "Callee-Allocates, Caller-Frees" contract. Every native `IntPtr` is released via a `finally` block to the `freeString` delegate, ensuring the unmanaged heap remains clean even during execution failures.

### 4. Telemetry & Observability

Integrated OpenTelemetry (OTLP) for end-to-end distributed tracing. W3C Trace IDs are propagated into the C++ layer to correlate native logs with specific REST requests.

```Bash
# Start the Jaeger collector and UI
./scripts/run-telemetry.sh start
```

- UI Dashboard: http://localhost:16686
- OTLP Endpoint: http://localhost:4317 (gRPC)

### 5. Hardware-Specific Optimization (Apple M2)

- **P-Core Saturation:** `MaxDegreeOfParallelism` is explicitly set to 4. This aligns with the M2's Performance Cores, ensuring heavy C++ string transformations maintain maximum IPC (Instructions Per Cycle) without being offloaded to Efficiency Cores.

Please note that if this runs in a Docker container on an Intel Xeon or AMD EPYC server (common in Production), ProcessorCount might be 64, but our code will still cap at 4.This is scope for future enhancement.

- Double-Lock Memory Safety: - Global: 20MB batch ceiling prevents the 8GB Unified Memory from triggering SSD swap.
  - Local: 5MB native limit prevents buffer overflows in unmanaged memory.
- Contention-Free Buffering:** Utilizes `ConcurrentBag<T>` to allow parallel P-Cores to flush data back to managed memory without the lock-contention overhead of traditional `List<T>` synchronization.

---

## Quick Start

Prerequisites

- Docker & Docker Compose
- Apple M2 (Recommended) or ARM64/x64 Linux/Windows

### Run the Load-Balanced Cluster

To support massive horizontal scaling, the system utilizes an NGINX Reverse Proxy as a Layer 7 Load Balancer. This architecture allows the API to scale beyond a single process, distributing load across multiple isolated containers.

- Dynamic Scaling: Orchestrated via Docker Compose with a replicas: 4 configuration, perfectly mapping to the M2's Performance Cores for maximum throughput.

- Health-Aware Routing: NGINX ensures traffic is only routed to "Ready" .NET instances, facilitating zero-downtime updates and maintenance.

- Performance Baseline: Validated through a 300,000-request soak test, achieving a sustained ~2,643 req/s with a 100% success rate.

- Latency Smoothing: By distributing requests, the P(95) latency is stabilized at 56ms, significantly reducing the "Tail Latency" spikes caused by parallel Garbage Collection events in managed memory.

To spin up the system with 4 backend replicas and the NGINX Load Balancer:

```Bash
docker compose -f docker-compose-load.yml up --scale backend=4 -d
```

- API Gateway: http://localhost:8080

- Frontend UI: http://localhost:5173

- Telemetry: http://localhost:16686

### Endurance & Stress Validation

The architecture was subjected to a 1,000,000-request ultra-stress test to validate long-term stability and memory integrity across the native boundary.

- Result: 100% Success Rate (0 failures).

- Sustained Throughput: ~2,511 req/s under 50 VU (Virtual User) concurrency.

- Stability: Zero native memory growth or heap fragmentation observed, confirming the efficacy of the Aggregate Memory Guard and RAII patterns in the C++ core.

- Tail Latency Control: Even at 1M iterations, the P(95) remained stable at 58.8ms, proving the system handles high-volume Garbage Collection (GC) pressure without process degradation.

---

### Technical Significance

- Leak-Proof Architecture: Stable Resident Set Size (RSS) proves the manual memory management and RAII patterns in the C++ layer are production-grade.

- Sustained Throughput: Maintaining an average latency of 0.45ms over a quarter-million requests proves there is no performance decay or "warm-up" penalty in the native bridge.

- Hardware Efficiency: Optimized for Apple Silicon (arm64), leveraging unified memory to minimize data copy overhead during managed-to-unmanaged transitions.

### Performance Metrics & Insights

- ABI Latency: Verification that data marshalling between System.String and char* remains under 1ms.

- Security Gate Logging: Native 5MB buffer violations are automatically tagged as Error status in the trace, allowing for instant debugging of failed payloads.

- Context Propagation: The W3C Trace ID is passed into the C++ engine, ensuring that native logs can be correlated back to specific API calls.

---

## License

Distributed under the Apache-2.0 License. See LICENSE for more information.

Nitish Singh - Software Systems Engineer

---

## Summary

Developed a cross-platform string conversion ecosystem utilizing a high-performance C++17 engine integrated into a .NET 8 microservice via P/Invoke. Engineered a Zero-Leak memory management policy across the ABI boundary and implemented a multi-stage Docker CI/CD pipeline supporting immutable artifact promotion across Dev, Staging, and Production environments.
