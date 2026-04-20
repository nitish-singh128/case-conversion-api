![C++ CI + Test](https://img.shields.io/github/actions/workflow/status/nitishhsinghhh/case-conversion-api/cpp-ci.yml?branch=main&label=C%2B%2B%20Core&style=flat-square)
![.NET API Status](https://img.shields.io/github/actions/workflow/status/nitishhsinghhh/case-conversion-api/dotnet-api.yml?branch=main&label=.NET%20API&style=flat-square)
![.NET API Integeration Tests](https://img.shields.io/github/actions/workflow/status/nitishhsinghhh/case-conversion-api/dotnet-tests.yml?branch=main&label=Integeration%20Tests&style=flat-square)
![Full Project Build](https://img.shields.io/github/actions/workflow/status/nitishhsinghhh/case-conversion-api/cpp-ci-DLL-all.yml?branch=main&label=Full%20Stack%20Build&style=flat-square)
![Docker Push](https://img.shields.io/github/actions/workflow/status/nitishhsinghhh/case-conversion-api/docker-build.yml?branch=main&label=Docker%20Registry&style=flat-square)
![Deployment](https://img.shields.io/github/actions/workflow/status/nitishhsinghhh/case-conversion-api/deploy.yml?branch=main&label=Production%20Deploy&style=flat-square)
![Deployment](https://img.shields.io/github/actions/workflow/status/nitishhsinghhh/case-conversion-api/cpp-quality.yml?branch=main&label=CPP%20Code%20Quality&style=flat-square)
![Telemetry E2E](https://img.shields.io/github/actions/workflow/status/nitishhsinghhh/case-conversion-api/telemetry-ci.yml?branch=main&label=Telemetry%20E2E&style=flat-square)
![Security Audit](https://img.shields.io/github/actions/workflow/status/nitishhsinghhh/case-conversion-api/codeql.yml?branch=main&label=CodeQL%20Advanced%20Security&style=flat-square)

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

The .NET service implements a **Double-Lock Security Gate** to ensure system stability across the ABI boundary:

```csharp
// Version 1.4: High-Performance Parallel Orchestration with Aggregate Guard
public async Task<IEnumerable<string>> ConvertBatchAsync(IEnumerable<string> inputs, int choice)
{
    if (inputs.Sum(s => (long)s.Length) > MaxBatchPayloadBytes)
        throw new ArgumentException($"Total batch payload exceeds the {MaxBatchPayloadBytes / 1024 / 1024}MB safety limit.");

    var options = new ParallelOptions { MaxDegreeOfParallelism = MaxNativeParallelism };
    var results = new ConcurrentBag<string>();

    await Parallel.ForEachAsync(inputs, options, async (input, cancellationToken) =>
    {
        string result = await Task.Run(() => Convert(input, choice), cancellationToken);
        results.Add(result);
    });

    return results;
}
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

---

## Performance Benchmarks & Stress Validation

The system was subjected to a high-concurrency soak test to validate the stability of the C++ Native Bridge and the .NET 8 Garbage Collector under extreme pressure.

### 100K Request Soak Test Results

| Metric | Result | Status |
| :--- | :--- | :--- |
| **Total Requests** | 100,000 (Sequential) | Pass |
| **Success Rate** | 100% (200 OK) | Pass |
| **Test Duration** | **172.7s** | Pass |
| **Memory Delta (RSS)** | < 20MB (Post-GC) | Stable |
| **Avg. Latency (ABI)** | ~0.45ms | Optimal |

> **Verification:** Zero native memory leaks detected across $10^5$ P/Invoke transitions. Unmanaged heap remained stable via the **"Callee-Allocates, Caller-Frees"** contract.

---

### Granular Latency

*Metrics captured via high-resolution internal telemetry and Middleware Diagnostics.*

| Pipeline Stage | Latency | Benchmark (Industry Avg) |
| :--- | :--- | :--- |
| **Logic Latency (C++ Core)** | **0.1661ms** | < 2.0ms |
| **P/Invoke Marshalling** | **< 0.1000ms** | — |
| **Total API Roundtrip** | **0.3140ms** | < 5.0ms |
| **Middleware Overhead** | **~0.1479ms** | < 1.0ms |

---

### Execution Log Trace (Snapshot)

The following trace confirms the sub-millisecond execution of the hot-path and a clean environment teardown after 100,000 iterations.

```log
info: Executed action WordCaseController.Convert (DotNetAPI) in 0.1661ms
info: Request finished HTTP/1.1 POST /api/WordCase/convert - 200 - 0.3140ms
dbug: Microsoft.Extensions.Hosting.Internal.Host[4] Hosting stopped
[xUnit.net 00:02:47.70] Finished: DotNetAPI.Tests (172.7s)
Test summary: total: 50, failed: 0, succeeded: 50
'''

### 200K Request Soak Test Results

| Metric | Result |
| :--- | :--- |
| **Total Requests** | 200,000 (Sequential) |
| **Success Rate** | 100% (200 OK) |
| **Memory Delta (RSS)** | < 20MB (Post-GC) |
| **Avg. Latency (ABI)** | ~2.5 ms |
| **Test Duration** | ~503.0 Seconds |

**The Math**

Total Requests (n): 200,000

Total Duration (T): 503.0 seconds

Latency per Request (L):  n/T

L= 200,000/503.0 s = 0.002515 seconds per request

To convert this to milliseconds (ms): 0.002515×1,000 = 2.515 ms

### 250K Request "Marathon" 

| Metric | Result | Status |
| :--- | :--- | :--- |
| **Total Requests** | **250,000** (Sequential) | Pass |
| **Success Rate** | 100% (200 OK) | Pass |
| **Test Duration** | **298.8s** (~5 Mins) | Pass |
| **Memory Delta (RSS)** | < 25MB (Post-GC) | Stable |
| **Avg. Roundtrip** | **0.4527ms** | Optimal |

> **Verification:** Zero native memory leaks detected across $2.5 \times 10^5$ P/Invoke transitions. The unmanaged heap remained stable, confirming the efficacy of the **"Callee-Allocates, Caller-Frees"** memory contract over extended runtimes.

| Pipeline Stage | Latency | Benchmark (Industry Avg) |
| :--- | :--- | :--- |
| **Total API Roundtrip** | **0.4527ms** | < 5.0ms |
| **Logic Latency (C++ Core)** | **~0.21ms** | < 2.0ms |
| **P/Invoke Marshalling** | **< 0.10ms** | — |
| **Middleware Overhead** | **~0.24ms** | < 1.0ms |


### Execution Log Trace (Snapshot)
The following trace confirms the stability of the hot-path and a clean environment teardown after a 250,000-iteration stress test.

```log
info: Request finished HTTP/1.1 POST /api/WordCase/convert - 200 - 0.4527ms
dbug: Microsoft.Extensions.Hosting.Internal.Host[4] Hosting stopped
[xUnit.net 00:04:54.11] Finished: DotNetAPI.Tests (298.8s)
Test summary: total: 46, failed: 0, succeeded: 46


### Reliability Through Pessimism: The 1M Request Milestone
While the 100K soak test validated the memory contract, expanding the stress boundary to **1,000,000 requests** revealed the physical limits of the host environment. 

- **The Senior Engineer Perspective:** At 1M requests, "perfect code" often fails unexpectedly. A standard approach might mistake this for a memory leak or a C++ crash.
- **The Staff Architect Perspective:** Diagnostic analysis identified **TCP Socket Exhaustion** at the kernel level. By recognizing that `TIME_WAIT` is a physical state in the TCP stack and that the OS has a finite supply of ephemeral ports, the system was tuned to manage its relationship with the OS network stack.
- **Resolution:** Implemented a system heartbeat and connection-pooling logic to ensure the hardware and OS could recycle resources at the same frequency as the high-speed P/Invoke transitions.

---

### Performance Metrics & Insights

- ABI Latency: Verification that data marshalling between System.String and char* remains under 1ms.

- Security Gate Logging: Native 5MB buffer violations are automatically tagged as Error status in the trace, allowing for instant debugging of failed payloads.

- Context Propagation: The W3C Trace ID is passed into the C++ engine, ensuring that native logs can be correlated back to specific API calls.

## Hardware-Specific Optimization (Apple M2)

- **P-Core Saturation:** `MaxDegreeOfParallelism` is explicitly set to 4. This aligns with the M2's Performance Cores, ensuring heavy C++ string transformations maintain maximum IPC (Instructions Per Cycle) without being offloaded to Efficiency Cores.
- Double-Lock Memory Safety: - Global: 20MB batch ceiling prevents the 8GB Unified Memory from triggering SSD swap.
  - Local: 5MB native limit prevents buffer overflows in unmanaged memory.
- Contention-Free Buffering:** Utilizes `ConcurrentBag<T>` to allow parallel P-Cores to flush data back to managed memory without the lock-contention overhead of traditional `List<T>` synchronization.

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

3. Defensive Interop Design

- Sentinel Pattern: The C++ engine returns a sentinel string (`ERROR_BUFFER_OVERFLOW_LIMIT_5MB`) upon security violation. The C# layer traps this and re-throws a managed `ArgumentException`, providing a clean error path for the API consumer.
- Reentrant & Stateless: The native engine maintains no global state. Every P/Invoke call operates on its own stack and heap allocation, ensuring full reentrancy for parallel execution.
- Zero-Footprint Disposal: Implements a strict "Callee-Allocates, Caller-Frees" contract. Every native `IntPtr` is released via a `finally` block to the `freeString` delegate, ensuring the unmanaged heap remains clean even during execution failures.

---

## Running the System

```Bash
docker compose up --build
```

This will start:

- Backend → http://localhost:8080
- Frontend → http://localhost:5173

---

## Project Impact & Community Validation

Since its release, this repository has served as a reference architecture for high-performance polyglot systems.

- **Adoption:** 4,800+ Clones in 14 days (verified via GitHub Traffic).
- **Engagement:** 3,200+ unique views with a high concentration on CI/CD workflow patterns.
- **Network Effect:** Significant referrals from LinkedIn and Engineering forums, validating the "Hardware-Aware" and "1M Request" benchmarks.
- **Industrial Interest:** Deep-dive audits of the `/workflows` directory suggest the industry is utilizing these YAML files as a blueprint for cross-platform C++/C# pipelines.

---

## Summary

Developed a cross-platform string conversion ecosystem utilizing a high-performance C++17 engine integrated into a .NET 8 microservice via P/Invoke. Engineered a Zero-Leak memory management policy across the ABI boundary and implemented a multi-stage Docker CI/CD pipeline supporting immutable artifact promotion across Dev, Staging, and Production environments.
