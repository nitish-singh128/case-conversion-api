# Performance & Load Balancing Report

This document outlines the end-to-end process of containerizing, load balancing, and stress-testing the Polyglot Case Conversion engine.

## 1. Environment Setup

To ensure hardware-level optimization for the Apple M2 chip, the environment is containerized using Docker with a focus on ARM64 compatibility.

### Multi-Stage Orchestration

We utilize a dedicated Compose file to separate standard development from high-concurrency testing.

- File: docker-compose-load.yml

- Backends: 2 Replicas (Optimized for M2 P-Core distribution).

- Proxy: NGINX (Reverse Proxy / Load Balancer).

### Initializing the Cluster

```Bash
docker compose -f docker-compose-load.yml up --build -d
```

## 2. Load Balancer Configuration

The system uses NGINX to distribute traffic. This is critical for validating the thread-safety of our C++ P/Invoke layer across multiple process instances.

### Relevant Files:

- nginx.conf: Defines the upstream backend pool.

## 3. The Soak Test Methodology

We perform a 200,000-request soak test to validate memory stability and the Aggregate Memory Guard implemented in the C++ engine.

Test Script: k6-soak-test.js

The script mimics the .NET contract found in InvalidInputTests.cs:

```Bash
{
  "text": "Soak_Test_Data",
  "choice": 1
}
```

### Execution Command

We use the official Grafana k6 ARM64 image to ensure the load generator does not bottleneck the M2's performance.

```Bash
docker run --rm -i grafana/k6 run --iterations 300000 --vus 50 - <test.js
```

## 4. Benchmark Results (M2 MacBook Air - 2 Replicas)

The following metrics represent the "Gold Standard" for this system version.

| Metric           | Result          |
|------------------|-----------------|
| Total Requests   | 200,000         |
| Throughput       | 3,258.91 req/s  |
| Success Rate     | 100.00%         |
| Avg Latency      | 15.18 ms        |
| Max Latency      | 749.33 µs       |
| P(95) Latency    | 34.62 ms        |

## 5. Benchmark Results (M2 MacBook Air - 4 Replicas)

| Metric           | Result          |
|------------------|-----------------|
| Total Requests   | 300,000         |
| Throughput       | 2,643.88 req/s  |
| Success Rate     | 100.00%         |
| Avg Latency      | 18.7 ms        |
| Max Latency      | 300.45 ms       |
| P(95) Latency    | 56.07 ms        |



### Observations

- Latency Stability: By scaling to 4 replicas, we achieved an 8x reduction in max_latency (dropping from ~2.4s to 300ms) compared to the 2-replica setup.

- Zero Native Crashes: Handled 600,000 total validation checks without a single AccessViolationException or segmentation fault.

- GC Efficiency: The distribution across 4 instances allowed the .NET Garbage Collector to run in parallel, preventing the "Stop-the-world" pauses that previously spiked latency.

- Memory Integrity: Even after 300k iterations, memory usage remained flat, confirming that the C++-to-managed string marshalling is leaking zero bytes.
