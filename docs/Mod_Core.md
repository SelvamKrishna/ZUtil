# Zen Utility Library Documentation

## Module (`zen::core`)

### Table of Contents

  1. [ANSI Escape Codes](#ansi-escape-codes)
  2. [Export Macros](#export-macros)
  3. [ProString - Colored String Wrapper](#prostring---colored-string-wrapper)
  4. [Assertion System](#assertion-system)
  5. [Logging System](#logging-system)
  6. [Testing Framework](#testing-framework)
  7. [Type Aliases](#type-aliases)
  8. [Utility Macros](#utility-macros)

## ANSI Escape Codes

`#include <zen/core/_ansi.hpp>`

### Overview

Provides ANSI escape sequences for terminal text formatting Works seamlessly with `std::ostream` and `std::format` by producing ANSI escape sequences. Can be globally disabled via `Z_DISABLE_ANSI`.

### Configuration

Macro | Description
---|---
`Z_DISABLE_ANSI` | When defined, disables all ANSI escape code output

### Enum `ANSI`

#### Text Styles

Value | Code | Description
---|---|---
`ANSI::Reset` | 0 | Reset all styles
`ANSI::Bold` | 1 | Bold text
`ANSI::Dim` | 2 | Dim text
`ANSI::Italic` | 3 | Italic text
`ANSI::Underline` | 4 | Underlined text
`ANSI::Blink` | 5 | Blinking text
`ANSI::Inverse` | 7 | Inverse colors
`ANSI::Hidden` | 8 | Hidden text
`ANSI::Strikethrough` | 9 | Strikethrough text

#### Foreground Colors

Standard | Extended
---|---
`ANSI::Black` (30) | `ANSI::EX_Black` (90)
`ANSI::Red` (31) | `ANSI::EX_Red` (91)
`ANSI::Green` (32) | `ANSI::EX_Green` (92)
`ANSI::Yellow` (33) | `ANSI::EX_Yellow` (93)
`ANSI::Blue` (34) | `ANSI::EX_Blue` (94)
`ANSI::Magenta` (35) | `ANSI::EX_Magenta` (95)
`ANSI::Cyan` (36) | `ANSI::EX_Cyan` (96)
`ANSI::White` (37) | `ANSI::EX_White` (97)

#### Background Colors

Standard | Extended
---|---
`ANSI::BG_Black` (40) | `ANSI::BG_EX_Black` (100)
`ANSI::BG_Red` (41) | `ANSI::BG_EX_Red` (101)
`ANSI::BG_Green` (42) | `ANSI::BG_EX_Green` (102)
`ANSI::BG_Yellow` (43) | `ANSI::BG_EX_Yellow` (103)
`ANSI::BG_Blue` (44) | `ANSI::BG_EX_Blue` (104)
`ANSI::BG_Magenta` (45) | `ANSI::BG_EX_Magenta` (105)
`ANSI::BG_Cyan` (46) | `ANSI::BG_EX_Cyan` (106)
`ANSI::BG_White` (47) | `ANSI::BG_EX_White` (107)

### Operators

Operator | Description
---|---
`std::ostream& operator<<(std::ostream&, const ANSI&)` | Stream insertion with automatic disabling

### Example Usage

```cpp
    // Stream output
    std::cout << zen::core::ANSI::Green << "Success!" << zen::core::ANSI::Reset << std::endl;

    // Format string
    std::string msg = std::format("{}{}{}",
        zen::core::ANSI::Red,
        "Error occurred",
        zen::core::ANSI::Reset);
```

## Export Macros

`#include <zen/core/_export.hpp>`

### Platform Detection

Macro | Description
---|---
`ZEN_PLATFORM_WINDOWS` | 1 on Windows platforms, 0 otherwise
`ZEN_COMPILER_GCC_LIKE` | 1 when compiler supports GCC-style attributes (GCC/Clang)

### Symbol Visibility

Macro | Description
---|---
`ZEN_API` | Proper DLL export/import or visibility attributes
`ZEN_BUILD` | Define when building the library (not using it)

## ProString - Colored String Wrapper

`#include <zen/core/_pro_string.hpp>`

### Overview

`ProString` encapsulates a string with an associated ANSI color code, providing convenient colored output for logging and debugging.

### Constructors

Constructor | Description
---|---
`ProString(std::string_view string, ANSI ansiCode = ANSI::Reset)` | From string view
`ProString(const char* string, ANSI ansiCode = ANSI::Reset)` | From C-string
`ProString(format_string<Args...>, Args&&...)` | From format string
`ProString(ANSI, format_string<Args...>, Args&&...)` | With explicit color
`ProString(const std::source_location&, bool isVerbose = false)` | From source location

### Member Functions

Function | Description
---|---
`ANSI GetColor() const` | Returns the ANSI color
`const std::string& GetString() const` | Returns the underlying string
`std::string GetParsedString() const` | Returns string with ANSI codes
`void SetColor(ANSI)` | Sets the ANSI color
`void SetString(std::string_view)` | Sets the string content
`void Clear()` | Clears the string

### Example Usage

```cpp
    // Create colored string
    zen::core::ProString errorMsg(zen::core::ANSI::Red, "Failed to open file: {}", filename);

    // Stream output
    std::cout << errorMsg << std::endl;

    // Use in formatting
    std::string log = std::format("Status: {}", errorMsg);

    // Source location
    zen::core::ProString location(std::source_location::current());
    std::cout << location << std::endl;  // Outputs: [file.cpp:42]
```

## Assertion System

`#include <zen/core/assert.hpp>`

### Overview

Enhanced assertion system with colored output and source location tracking. Disabled in release builds unless explicitly forced.

### Functions

Function | Description
---|---
`void Assert(bool condition, const ProString& description, const std::source_location& sourceLocation)` | Assert with optional always-on behavior

### Example Usage

```cpp
    // Debug-only assert
    zen::core::Assert(ptr != nullptr, "Pointer cannot be null");

    // Always-on assert (even in release)
    zen::core::Assert<true>(initialized, "System must be initialized");

    // With automatic source location
    zen::core::Assert(result == 0, ProString(ANSI::Red, "Operation failed with code: {}", result));
```

## Logging System

`#include <zen/core/logger.hpp>`

### Configuration

Macro | Description
---|---
`Z_DISABLE_LOGGING` | When defined, disables all logging output

### Enum `LogLevel`

Level | Description
---|---
`LogLevel::DBG` | Debug information (Blue)
`LogLevel::INFO` | Informational message (Green)
`LogLevel::WARN` | Warning condition (Yellow)
`LogLevel::ERR` | Error condition (Red)

### Core Logging Functions

Function | Description
---|---
`Log(level, message, context = "")` | Log with automatic disabling

### Logger Class

Base class providing contextual logging with persistent prefixes.

#### Constructors

Constructor | Description
---|---
`Logger(const ProString& context)` | Single context tag
`Logger(const std::vector<ProString>&)` | Multiple context tags

#### Protected Methods

Method | Description
---|---
`Log(level, message)` | Log with stored context
`AddContext(const ProString&)` | Append context tag
`GetContext()` | Get context string

### ScopeDiagnostic Class

RAII helper for scoped operations with automatic logging of entry/exit.

#### Constructor

```cpp
    ScopeDiagnostic(
        const ProString& operationDesc = "",
        const Logger* classLogger = nullptr,
        bool isVerbose = false,
        const std::source_location& = std::source_location::current()
    )
```

#### Methods

Method | Description
---|---
`FailAbort(const ProString&)` | Log error and abort
`FailWarn(const ProString&)` | Log warning
`Success(const ProString&)` | Log success

### Example Usage

```cpp
    // Simple logging
    zen::core::Log(zen::core::LogLevel::INFO, "Application started");

    // Logger inheritance
    class Renderer : public zen::core::Logger {
    public:
        Renderer() : Logger({"[RENDERER]"}) {}

        void Render() {
            this->Log(zen::core::LogLevel::DBG, "Rendering frame");
        }
    };

    // Scope diagnostic
    {
        zen::core::ScopeDiagnostic diag("Loading texture", &logger, true);

        if (!texture.Load()) {
            diag.FailAbort("Failed to load texture");
        }

        diag.Success("Texture loaded");
    } // Automatically logs exit in verbose mode
```

## Testing Framework

`#include <zen/core/test.hpp>`

### Configuration

Macro | Description
---|---
`Z_DISABLE_TESTING` | When defined, disables all test output

### Core Test Function

```cpp
    void Test(
        bool condition,
        const ProString& description,
        const ProString& contextTag = {"\n[TEST]", ANSI::Blue}
    )
```

### TestSuite Class

Groups test cases with automatic summary reporting.

#### Constructor

```cpp
    TestSuite(const ProString& description)
```

#### Methods

Method | Description
---|---
`AddCase(bool result, const ProString& desc)` | Add and log test case
`GetPassedCount()` | Number of passed tests
`GetFailedCount()` | Number of failed tests
`GetTotalCount()` | Total number of tests

### Example Usage

```cpp
    {
        zen::core::TestSuite suite("Math Operations");

        suite.AddCase(2 + 2 == 4, "Addition works");
        suite.AddCase(5 * 5 == 25, "Multiplication works");
        suite.AddCase(10 / 2 == 5, "Division works");

        // Summary automatically logged on destruction
    } // Outputs: Passed: 3, Failed: 0, Total: 3

    // Individual test
    zen::core::Test(ptr != nullptr, "Pointer validation");
```

## Type Aliases

`#include <zen/core/types.hpp>`

### Integer Types

Signed | Unsigned | Size
---|---|---
`i8` | `u8` | 1 byte
`i16` | `u16` | 2 bytes
`i32` | `u32` | 4 bytes
`i64` | `u64` | 8 bytes

### Floating Point Types

Type | Description
---|---
`f32` | 32-bit float
`f64` | 64-bit double

### Size/Pointer Types

Type | Description
---|---
`usize` | std::size_t
`isize` | std::ptrdiff_t
`uptr` | std::uintptr_t
`iptr` | std::intptr_t
`byte` | std::byte

### Character Types

Type | Description
---|---
`char8` | char (UTF-8)
`char16` | char16_t (UTF-16)
`char32` | char32_t (UTF-32)
`wchar` | wchar_t

## Utility Macros

`#include <zen/core/macros.hpp>`

### Build Mode Detection

Macro | Description
---|---
`BUILD_DEBUG` | true in debug builds (NDEBUG not defined)
`Z_ON_DBG` | Execute code only in debug builds
`Z_ON_RLS` | Execute code only in release builds

### Logging Helpers

Macro | Description
---|---
`Z_VAR_SPLAT(var)` | Expands to "name = (value)" with colored name
`Z_CND_SPLAT(cond)` | Expands to (cond), "cond" for assertions

### Compiler Hints

Macro | Description
---|---
`Z_LIKELY(x)` | Hint that condition is likely true
`Z_UNLIKELY(x)` | Hint that condition is likely false
`Z_FORCE_INLINE` | Force function inlining
`Z_NO_INLINE` | Prevent function inlining
`Z_UNREACHABLE()` | Mark code as unreachable
`Z_TODO(msg)` | Compile-time TODO reminder

### String/Token Utilities

Macro | Description
---|---
`Z_STRINGIFY(x)` | Convert token to string
`Z_EXPAND_AND_STRINGIFY(x)` | Expand then stringify
`Z_CONCAT(a, b)` | Concatenate tokens
`Z_UNIQUE_NAME(base)` | Generate unique identifier with line number

### Bit Utilities

Macro | Description
---|---
`Z_BIT(pos)` | Create bit mask at position

### Example Usage

```cpp
    // Build-specific code
    Z_ON_DBG {
        std::cout << "Debug information" << std::endl;
    }

    // Likely/unlikely hints
    if (Z_UNLIKELY(ptr == nullptr)) {
        handleError();
    }

    // Variable splat for logging
    int health = 42;
    std::cout << std::format("{}", Z_VAR_SPLAT(health)) << std::endl;
    // Output: "health = (42)" with "health" in magenta

    // Unique name generation
    auto Z_UNIQUE_NAME(counter) = 0;  // Creates counter_42 (based on line)

    // TODO reminder
    Z_TODO("Optimize this algorithm");
```

## Summary

The Zen Core Library provides a comprehensive set of utilities for C++ development including:

  * **ANSI** - Terminal formatting with automatic disabling
  * **ProString** - Colored string wrapper for elegant output
  * **Assert** - Enhanced assertion with source location
  * **Logger** - Contextual logging with proper prefixes
  * **Test** - Simple testing framework with test suites
  * **Types** - Consistent type aliases across platforms
  * **Macros** - Utility macros for common patterns

**Note:** Most features support compile-time disabling via macros
(`Z_DISABLE_ANSI`, `Z_DISABLE_LOGGING`, `Z_DISABLE_TESTING`) for release builds.

