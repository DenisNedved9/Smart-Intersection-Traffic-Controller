Smart Intersection Traffic Controller

A lightweight C-based traffic management simulator that ingests raw binary telemetry from multiple intersection cameras, dynamically allocates buffer space, and evaluates traffic density and priority vehicles to optimize green light scheduling.

Problem & Purpose

Fixed-interval traffic lights cause unnecessary delays when traffic flow is asymmetric or when priority vehicles (e.g., ambulances) are present. Modern smart city infrastructure relies on camera telemetry sent via compact binary streams to dynamically adjust signal phases.

This project implements:

Binary Data Parsing: Ingestion of binary stream files (cameras.bin) containing camera identifier, waiting vehicle count, and priority status.

Dynamic Memory Reallocation: Automated buffer scaling using malloc and realloc to handle variable stream sizes.

Priority-Based Traffic Logic: Decision engine that prioritizes emergency vehicles while optimizing standard flow based on directional car counts.

Human-Readable Reporting: Complete diagnostic logging to text files (cameras_info.text).

File Overview

camera_simulator.c — Simulates telemetry data across 4 directional cameras (North, South, East, West) and exports binary records.

traffic_processor.c — Reads binary camera frames, manages dynamic buffer allocation, evaluates priority rules, and logs decision cycles.

cameras_info.text — Decoded diagnostic report detailing individual camera inputs and resulting signal state changes.
