# Case Conversion API — Design Document

## 1. Overview

The Case Conversion API is a multi-layered system that exposes a high-performance C++ string conversion engine through a .NET REST API and serves it to a React-based frontend UI. The architecture separates performance-critical logic from API orchestration and UI concerns.

The system uses native C++ for efficient string transformations, .NET for service exposure, and Docker for containerized deployment.

---

## 2. Goals

* Provide multiple string conversion strategies
* Ensure high performance using native C++
* Expose conversions via REST API
* Support containerized deployment
* Maintain modular and extensible architecture
* Enable cross-platform shared library usage

---

## 3. Non-Goals

* Persistent storage
* Authentication/authorization
* Distributed scaling
* Streaming or batch processing

---

## 4. High-Level Architecture

```
        Frontend (React)
        |
        v
        ASP.NET Core REST API
        |
        v
        P/Invoke Interop Layer
        |
        v
        C++ Shared Library
        |
        v
        Strategy Pattern Conversion Engine
```
---

## 5. Component Design

### 5.1 C++ Conversion Engine

Responsibilities:

* Implement conversion strategies
* Dispatch based on user choice
* Return processed string

Design Patterns:

* Strategy Pattern
* Factory Pattern
* Dispatcher

Example Strategies:

* AlternatingCase
* CapitalizeWords
* SnakeCase
* KebabCase
* LeetSpeak
* Reverse
* ToggleCase

Factory selects strategy:
Input Choice → Factory → Strategy → Execute

---

### 5.2 Shared Library Export Layer

The engine is exposed via a C-compatible interface.

Exported Function:

```C++
extern "C" const char* processStringDLL(const char* input, int choice);
```

Responsibilities:

* Bridge C++ and C#
* Dispatch conversion request
* Return C-style string pointer

---

### 5.3 .NET Interop Layer

Uses P/Invoke to call native DLL.

```C++
[DllImport("ProcessString")]
private static extern IntPtr processStringDLL(string input, int choice);
```

Responsibilities:

* Marshal strings
* Convert IntPtr to managed string
* Handle API-level validation

---

### 5.4 REST API Layer

Endpoint:
POST /api/WordCase/convert

Request:
{
"input": "hello world",
"choice": 1
}

Response:
{
"output": "hElLo WoRlD"
}

Responsibilities:

* Input validation
* Call service layer
* Return JSON response

---

### 5.5 Frontend UI

Technology:

* React
* TypeScript
* Vite

Responsibilities:

* Collect input
* Provide conversion selection
* Call REST API
* Display results

---

## 6. Build & Deployment Architecture

### Multi-stage Docker Build

Stage 1:

* Build C++ shared library
* Publish .NET API

Stage 2:

* Copy artifacts
* Run ASP.NET runtime

---

## 7. Runtime Flow

```
            User Input (React)
            ↓
            REST API Call
            ↓
            ASP.NET Controller
            ↓
            ProcessStringService
            ↓
            P/Invoke
            ↓
            processStringDLL (C++)
            ↓
            Factory
            ↓
            Strategy
            ↓
            Result
            ↓
            API Response
            ↓
            Frontend Display
```
---

## 8. Error Handling

* Invalid choice → return lower case of string
* Null input → return empty string
* DLL load failure → HTTP 500
* API validation failure → HTTP 400

---

## 9. Performance Considerations

* Native C++ for string processing
* No heap allocations in critical path
* Static buffer reuse
* Minimal interop overhead

---

## 10. Extensibility

To add new conversion:

1. Create new Strategy class
2. Implement convert()
3. Register in Factory
4. Update enum mapping

No API changes required.

---

## 11. Testing Strategy

C++:

* GoogleTest unit tests
* Strategy validation

.NET:

* Service layer tests

Integration:

* API endpoint tests

---

## 12. Deployment

Backend:
Docker container on port 8080

Frontend:
Docker container on port 5173

Docker Compose orchestrates:

* frontend
* backend

---

## 13. Future Improvements

* SIMD optimizations
* Async API calls
* Plugin-based strategies
* Benchmark endpoints
* WASM build of C++ engine

---

## 14. Tech Stack

```
C++ — Conversion engine
CMake — Build system
GoogleTest — Unit tests
.NET 8 — REST API
React + TypeScript — UI
Docker — Containerization
GitHub Actions — CI/CD
```
---

## 15. Key Design Decisions

Decision: Use C++ for conversions
Reason: Performance and native interop demonstration

Decision: Use P/Invoke
Reason: Lightweight interop vs gRPC/native hosting

Decision: Strategy Pattern
Reason: Extensible conversion types

Decision: Multi-stage Docker
Reason: Smaller runtime image

---

## 16. Tradeoffs

Pros:

* High performance
* Modular design
* Extensible architecture

Cons:

* Native interop complexity
* Memory management risks
* Cross-platform build complexity

---
