# ZEN Utility Library

ZEN is a lightweight, cross-platform C++ utility library providing general-purpose tools for strings, math, containers, logging, and more. Designed to simplify common programming tasks and provide a foundation for both header-only and DLL-style projects.

## Features

Zen Util Library aims to provide:

- Cross-platform compatibility.
- Simple, reusable utility components.

- **Developement tools :**
    - Logging, Testing, Assertion.
    - Common Helpful Macros.
    - ANSI color coded terminal output.
    - Clean primitive types re-definition.

- **Math operations :**
    - **Random and procedural utilities :** Uniform, Normal & Discrete distributions.

    - **Angle utilities :** Degree-Radian conversion, Trignometric functions.

    - **Vector utilities :**
        - Arithmetic operation, Boolean comparisons.
        - Rotation, Transformation & Other common vector calculations.

- **Containers :**
    - **Double Buffer :**
        - Provides two buffers that swap roles between read and write operations.
        - Useful for multi-threaded updates, rendering pipelines, or staged data updates.

    - **Fast Access Buffer :**
        - Optimized array-like structure for rapid element access and minimal overhead.
        - Ideal for high-performance loops and real-time systems.

    - **Iterator Wrapper :**
        - Lightweight wrapper around iterators to standardize iteration patterns.
        - Provides safe random access, range-based utilities, and integration with algorithms.

    - **Object Pool :**
        - Pre-allocates objects and reuses them to avoid frequent heap allocations.
        - Reduces memory fragmentation and improves performance in real-time systems.

    - **Spares Set :**
        - Maintains a set of reusable “slots” for sparse data storage.
        - Efficient for managing entities, IDs, or components with gaps in dense arrays.

## Setup

**Clone github repository**

```shell
git clone https://github.com/SelvamKrishna/ZenUtil.git zenutil
cd zenutil
```

## Requirements

Make sure the following tools are installed:

- **[CMake](https://cmake.org/download/)**
- **C++ compiler**
    - GCC/MinGW
    - Clang
    - MSVC
- **[Python (optional)](https://python.org/downloads/)**

## Build Options
### Option 1 — Using the Python build script (recommended)

Run the provided script:

```shell
python build.py
```

Optional commands:

```shell
python build.py clean
python build.py test
```

This script will:

- Configure the CMake project
- Build the library
- Optionally run development tests

### Option 2 — Using CMake directly

Configure the project:

```shell
cmake -S . -B build -G "GeneratorName" -DCMAKE_BUILD_TYPE=Release
```

Then build:

```shell
cmake --build build --parallel
```

Example (MinGW):

```shell
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
```
