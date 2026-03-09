# ZEN Utility Library

ZEN is a lightweight, cross-platform C++ utility library providing general-purpose tools for strings, math, containers, logging, and more. Designed to simplify common programming tasks and provide a foundation for both header-only and DLL-style projects.

## Project Goals

Zen Util Library aims to provide:

. Logging, Testing and Benchmarking tools
. Simple, reusable utility components
. Minimal dependencies
. Cross-platform compatibility

## Setup

**Clone github repository**

```shell
git clone https://github.com/SelvamKrishna/ZenUtil.git zenutil
cd zenutil
```

## Requirements

Make sure the following tools are installed:

. **[CMake](https://cmake.org/download/)**
. **C++ compiler**
    . GCC/MinGW
    . Clang
    . MSVC
. **[Python (optional)](https://python.org/downloads/)**

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

. configure the CMake project
. build the library
. optionally run development tests

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
