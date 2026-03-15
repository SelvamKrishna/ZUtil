# Zen Utility Library Documentation

## Module (`zen::container`)

### Overview

The `zen::container` module provides a collection of specialized data structures optimized for different
use cases in systems programming, game development, and high-performance applications. Each container
is designed with specific performance characteristics and memory access patterns in mind.

### Table of Contents

1. [DoubleBuffer](#doublebuffer)
2. [FastAccessBuffer](#fastaccessbuffer)
3. [IteratorWrapper](#iteratorwrapper)
4. [ObjectPool](#objectpool)
5. [SparseSet](#sparseset)

## DoubleBuffer

```cpp
    #include <zen/container/double_buffer.hpp>
```

### `template<typename DataT> struct DoubleBuffer`

Double-buffered storage container that maintains two instances of a data object: a read buffer and a write buffer.
This pattern is particularly useful for thread-safe data sharing where one thread writes data while another reads
it, or for implementing double-buffered rendering techniques.

### Template Parameters

| Parameter | Description                                                           |
| --------- | --------------------------------------------------------------------- |
| `DataT`   | Type of data stored in the buffers. Can be any copyable/movable type. |

### Public Types

| Type Alias   | Description                                     |
| ------------ | ----------------------------------------------- |
| `WBufferRef` | Mutable reference to write buffer (`DataT&`)    |
| `RBufferRef` | Const reference to read buffer (`const DataT&`) |

### Constructors

| Constructor                                       | Description                                                        |
| ------------------------------------------------- | ------------------------------------------------------------------ |
| `DoubleBuffer(DataT readValue, DataT writeValue)` | Constructs the double buffer with initial values for both buffers. |

### Member Functions

| Function                           | Description                                                      | Complexity |
| ---------------------------------- | ---------------------------------------------------------------- | ---------- |
| `RBufferRef Read() const noexcept` | Returns the current read buffer (const access)                   | O(1)       |
| `WBufferRef Write() noexcept`      | Returns the current write buffer (mutable access)                | O(1)       |
| `void Swap() noexcept`             | Exchanges read and write buffers and clears the new write buffer | O(1)       |

### Example Usage

```cpp
    // Create a double buffer for a game object
    zen::container::DoubleBuffer<Transform> transformBuffer{
        Transform{},  // Initial read buffer
        Transform{}   // Initial write buffer
    };

    // Writer thread
    auto& writeTransform = transformBuffer.Write();
    writeTransform.position = {10, 20, 30};
    writeTransform.rotation = {0, 90, 0};
    transformBuffer.Swap();  // Publish changes

    // Reader thread
    const auto& readTransform = transformBuffer.Read();
    renderObject(readTransform);
```

### Implementation Details

```cpp
    private:
        std::array<DataT, 2> _buffers; ///< Internal storage for the two buffers
        size_t _readIndex  = 0; ///< Index of the buffer used for reading
        size_t _writeIndex = 1; ///< Index of the buffer used for writing
```

## FastAccessBuffer

```cpp
    #include <zen/container/fast_access_buffer.hpp>
```

### `template<typename DataT> struct FastAccessBuffer`

ID-based storage container. Elements are stored sorted by ID to allow binary search lookup,
While maintaining cache-friendly memory layout.

### Template Parameters

| Parameter | Description                        |
| --------- | ---------------------------------- |
| `DataT`   | Type of data stored in the buffer. |

### Private Types

| Type              | Description                                       |
| ----------------- | ------------------------------------------------- |
| `_IdentifiedData` | Internal structure pairing an ID with stored data |

### Public Types

| Type       | Description                                     |
| ---------- | ----------------------------------------------- |
| `DataRef`  | Mutable reference to stored data (`DataT&`)     |
| `CDataRef` | Const reference to stored data (`const DataT&`) |

### Constructors

| Constructor                                   | Description                                   |
| --------------------------------------------- | --------------------------------------------- |
| `FastAccessBuffer(size_t reserveBuffer = 32)` | Constructs the buffer with reserved capacity. |

### Member Functions

| Function                                      | Description                           | Complexity |
| --------------------------------------------- | ------------------------------------- | ---------- |
| `bool Contains(size_t dataID) const noexcept` | Checks if an ID exists in the buffer  | O(log N)   |
| `size_t Insert(DataT&& data)`                 | Inserts new data, returns assigned ID | O(N)       |
| `void Remove(size_t dataID)`                  | Removes data by ID                    | O(N)       |
| `size_t Size() const noexcept`                | Returns number of stored elements     | O(1)       |
| `DataRef operator[](size_t dataID)`           | Access data by ID (mutable)           | O(log N)   |
| `CDataRef operator[](size_t dataID) const`    | Access data by ID (const)             | O(log N)   |

### ID Management

- IDs are either generated sequentially or recycled from removed elements
- Free IDs are stored in `_freeIDs` vector for reuse
- Maintains ascending ID order automatically

### Example Usage

```cpp
    zen::container::FastAccessBuffer<Player> playerBuffer;

    // Insert players
    size_t player1ID = playerBuffer.Insert(Player{"Alice", 100});
    size_t player2ID = playerBuffer.Insert(Player{"Bob", 85});

    // Access by ID
    if (playerBuffer.Contains(player1ID)) {
        auto& player = playerBuffer[player1ID];
        player.health -= 10;
    }

    // Remove player
    playerBuffer.Remove(player2ID);
```

### Implementation Details

```cpp
    private:
        struct _IdentifiedData {
            size_t id;   ///< Unique identifier
            DataT data;  ///< Stored value
        };

        std::vector<_IdentifiedData> _dataBuffer; ///< Sorted storage buffer
        std::vector<size_t> _freeIDs;             ///< Recycled IDs
        size_t _currentID = 0;                    ///< Next generated ID
```

## IteratorWrapper

```cpp
    #include <zen/container/iterator_wrapper.hpp>
```

### `template<std::forward_iterator IteratorT> struct IteratorWrapper`

Lightweight utility class that wraps an iterator range, providing a unified interface for working with iterator pairs. Particularly useful for algorithm implementations and range-based operations.

### Template Parameters

| Parameter   | Description                                                   |
| ----------- | ------------------------------------------------------------- |
| `IteratorT` | Iterator type that satisfies `std::forward_iterator` concept. |

### Type Aliases

| Alias               | Description                               |
| ------------------- | ----------------------------------------- |
| `iterator_category` | Iterator category of the wrapped iterator |
| `value_type`        | Type of elements in the range             |
| `difference_type`   | Iterator difference type                  |
| `pointer`           | Pointer to element type                   |
| `reference`         | Reference to element type                 |

### Constructors

| Constructor                                           | Description                            |
| ----------------------------------------------------- | -------------------------------------- |
| `IteratorWrapper(IteratorT itBegin, IteratorT itEnd)` | Constructs from explicit iterator pair |

| `IteratorWrapper<<!DOCTYPE html>

<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Zen Math Library Documentation</title>
    <style>
        body {
            font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, Oxygen, Ubuntu, Cantarell, sans-serif;
            line-height: 1.6;
            color: #333;
            max-width: 1200px;
            margin: 0 auto;
            padding: 20px;
        }
        h1, h2, h3 {
            color: #2c3e50;
        }
        h1 {
            border-bottom: 3px solid #3498db;
            padding-bottom: 10px;
        }
        h2 {
            border-bottom: 2px solid #3498db;
            padding-bottom: 5px;
            margin-top: 30px;
        }
        h3 {
            color: #2980b9;
            margin-top: 25px;
        }
        h4 {
            color: #7f8c8d;
            margin-top: 20px;
        }
        pre {
            background: #f8f9fa;
            padding: 15px;
            border-radius: 5px;
            overflow-x: auto;
            border: 1px solid #e1e1e1;
        }
        code {
            background: #f8f9fa;
            padding: 2px 5px;
            border-radius: 3px;
            font-family: 'Courier New', Courier, monospace;
            color: #e74c3c;
        }
        pre code {
            background: none;
            padding: 0;
            color: #333;
        }
        table {
            border-collapse: collapse;
            width: 100%;
            margin: 15px 0;
        }
        th, td {
            border: 1px solid #ddd;
            padding: 12px;
            text-align: left;
        }
        th {
            background-color: #3498db;
            color: white;
        }
        tr:nth-child(even) {
            background-color: #f2f2f2;
        }
        .note {
            background-color: #e7f3fe;
            border-left: 4px solid #2196F3;
            padding: 10px 15px;
            margin: 20px 0;
        }
        .warning {
            background-color: #fff3cd;
            border-left: 4px solid #ffc107;
            padding: 10px 15px;
            margin: 20px 0;
        }
        .toc {
            background-color: #f8f9fa;
            padding: 20px;
            border-radius: 5px;
            margin: 20px 0;
        }
        .toc ul {
            list-style-type: none;
            padding: 0;
        }
        .toc li {
            margin: 5px 0;
        }
        .toc a {
            color: #3498db;
            text-decoration: none;
        }
        .toc a:hover {
            text-decoration: underline;
        }
        .badge {
            display: inline-block;
            padding: 3px 8px;
            border-radius: 3px;
            font-size: 0.8em;
            font-weight: bold;
            margin-right: 5px;
        }
        .badge-primary { background: #3498db; color: white; }
        .badge-success { background: #2ecc71; color: white; }
        .badge-warning { background: #f39c12; color: white; }
        .badge-danger { background: #e74c3c; color: white; }
        .method {
            font-family: 'Courier New', Courier, monospace;
            background-color: #eef2f3;
            padding: 2px 5px;
            border-radius: 3px;
        }
    </style>
</head>
<body>
    <h1>Zen Math Library Documentation</h1>

    <div class="toc">
        <h2>Table of Contents</h2>
        <ul>
            <li><a href="#angle">1. Angle - Type-Safe Angle Representation</a></li>
            <li><a href="#constants">2. Mathematical Constants</a></li>
            <li><a href="#random">3. Random Number Generation</a></li>
            <li><a href="#trigonometry">4. Trigonometric Functions</a></li>
            <li><a href="#utils">5. Utility Functions</a></li>
            <li><a href="#vec2">6. Vec2 - 2D Vector Mathematics</a></li>
        </ul>
    </div>

    <!-- Angle Module -->
    <h2 id="angle">Angle - Type-Safe Angle Representation</h2>
    <p><code>#include &lt;zen/math/angle.hpp&gt;</code></p>

    <h3>Overview</h3>
    <p>The <code>Angle</code> type provides a type-safe abstraction over raw floating-point values when working with rotations or angular measurements. Angles are stored internally in radians but can be created from and converted to degrees.</p>

    <h3>Conversion Functions</h3>
    <table>
        <tr><th>Function</th><th>Description</th></tr>
        <tr><td><code>DegreesToRadians(f32 degrees)</code></td><td>Converts degrees to radians</td></tr>
        <tr><td><code>RadiansToDegrees(f32 radians)</code></td><td>Converts radians to degrees</td></tr>
    </table>

    <h3>Static Factory Methods</h3>
    <table>
        <tr><th>Method</th><th>Description</th></tr>
        <tr><td><code>Angle::FromRadians(f32 radians)</code></td><td>Creates angle from radians</td></tr>
        <tr><td><code>Angle::FromDegrees(f32 degrees)</code></td><td>Creates angle from degrees</td></tr>
    </table>

    <h3>Member Functions</h3>
    <table>
        <tr><th>Function</th><th>Description</th></tr>
        <tr><td><code>AsRadians()</code></td><td>Returns angle in radians</td></tr>
        <tr><td><code>AsDegrees()</code></td><td>Returns angle in degrees</td></tr>
        <tr><td><code>Normalized()</code></td><td>Returns angle normalized to [0, 2π)</td></tr>
        <tr><td><code>Sin()</code></td><td>Computes sine of the angle</td></tr>
        <tr><td><code>Cos()</code></td><td>Computes cosine of the angle</td></tr>
        <tr><td><code>Tan()</code></td><td>Computes tangent of the angle</td></tr>
    </table>

    <h3>Operators</h3>
    <table>
        <tr><th>Operator</th><th>Description</th></tr>
        <tr><td><code>+, -, *, /</code></td><td>Arithmetic operations</td></tr>
        <tr><td><code>+=, -=</code></td><td>Compound assignment</td></tr>
        <tr><td><code>==, !=, &lt;, &gt;, &lt;=, &gt;=</code></td><td>Comparison operators (with epsilon tolerance)</td></tr>
    </table>

    <h3>Example Usage</h3>
    <pre><code>// Create angles

auto rightAngle = zen::math::Angle::FromDegrees(90.0f);
auto piAngle = zen::math::Angle::FromRadians(zen::math::constants::F32_PI);

// Conversions
float degrees = rightAngle.AsDegrees(); // 90.0f
float radians = rightAngle.AsRadians(); // π/2

// Trigonometric functions
float sinVal = rightAngle.Sin(); // 1.0f
float cosVal = rightAngle.Cos(); // 0.0f

// Normalization
auto largeAngle = zen::math::Angle::FromDegrees(450.0f);
auto normalized = largeAngle.Normalized(); // 90 degrees

// Arithmetic
auto sum = rightAngle + piAngle;
auto doubled = rightAngle \* 2.0f;</code></pre>

    <!-- Constants Module -->
    <h2 id="constants">Mathematical Constants</h2>
    <p><code>#include &lt;zen/math/constants.hpp&gt;</code></p>

    <h3>Overview</h3>
    <p>Comprehensive set of mathematical and numeric constants for both 32-bit and 64-bit types.</p>

    <h3>Integer Limits</h3>
    <table>
        <tr><th>Signed</th><th>Unsigned</th></tr>
        <tr>
            <td><code>I8_MIN, I8_MAX</code><br><code>I16_MIN, I16_MAX</code><br><code>I32_MIN, I32_MAX</code><br><code>I64_MIN, I64_MAX</code></td>
            <td><code>U8_MAX</code><br><code>U16_MAX</code><br><code>U32_MAX</code><br><code>U64_MAX</code></td>
        </tr>
    </table>

    <h3>Floating Point Limits</h3>
    <table>
        <tr><th>32-bit</th><th>64-bit</th><th>Description</th></tr>
        <tr><td><code>F32_MIN</code></td><td><code>F64_MIN</code></td><td>Minimum positive normal</td></tr>
        <tr><td><code>F32_LOWEST</code></td><td><code>F64_LOWEST</code></td><td>Most negative finite value</td></tr>
        <tr><td><code>F32_MAX</code></td><td><code>F64_MAX</code></td><td>Maximum finite value</td></tr>
        <tr><td><code>F32_EPSILON</code></td><td><code>F64_EPSILON</code></td><td>Machine epsilon</td></tr>
        <tr><td><code>F32_COMPARE_EPSILON</code></td><td><code>F64_COMPARE_EPSILON</code></td><td>1e-4f (comparison tolerance)</td></tr>
        <tr><td><code>F32_NORMAL_EPSILON</code></td><td><code>F64_NORMAL_EPSILON</code></td><td>1e-8f (normalization tolerance)</td></tr>
        <tr><td><code>F32_INFINITY</code></td><td><code>F64_INFINITY</code></td><td>Positive infinity</td></tr>
        <tr><td><code>F32_NEG_INFINITY</code></td><td><code>F64_NEG_INFINITY</code></td><td>Negative infinity</td></tr>
    </table>

    <h3>Mathematical Constants</h3>
    <table>
        <tr><th>32-bit</th><th>64-bit</th><th>Description</th></tr>
        <tr><td><code>F32_PI</code></td><td><code>F64_PI</code></td><td>π (3.14159...)</td></tr>
        <tr><td><code>F32_TWO_PI</code></td><td><code>F64_TWO_PI</code></td><td>2π</td></tr>
        <tr><td><code>F32_TAU</code></td><td><code>F64_TAU</code></td><td>τ (2π) - alias</td></tr>
        <tr><td><code>F32_HALF_PI</code></td><td><code>F64_HALF_PI</code></td><td>π/2</td></tr>
        <tr><td><code>F32_INV_PI</code></td><td><code>F64_INV_PI</code></td><td>1/π</td></tr>
        <tr><td><code>F32_GOLDEN_RATIO</code></td><td><code>F64_GOLDEN_RATIO</code></td><td>φ (1.61803...)</td></tr>
    </table>

    <!-- Random Module -->
    <h2 id="random">Random Number Generation</h2>
    <p><code>#include &lt;zen/math/random.hpp&gt;</code></p>

    <h3>Overview</h3>
    <p>Comprehensive random number generation utilities with support for various distributions and container-based random selection.</p>

    <h3>Global Engine Control</h3>
    <table>
        <tr><th>Function</th><th>Description</th></tr>
        <tr><td><code>GetEngine()</code></td><td>Returns reference to global Mersenne Twister engine</td></tr>
        <tr><td><code>GenerateSeed()</code></td><td>Generates random seed using system entropy</td></tr>
        <tr><td><code>SetSeed(u32 value)</code></td><td>Seeds the global random engine</td></tr>
    </table>

    <h3>Distribution Templates</h3>
    <table>
        <tr><th>Function</th><th>Description</th></tr>
        <tr><td><code>UniformDistribution&lt;NumericT&gt;(min, max)</code></td><td>Uniform distribution (integral or floating-point)</td></tr>
        <tr><td><code>NormalDistribution&lt;NumericT&gt;(mean, stddev)</code></td><td>Normal (Gaussian) distribution</td></tr>
        <tr><td><code>DiscreteDistribution(weights)</code></td><td>Weighted discrete distribution using IteratorWrapper</td></tr>
    </table>

    <h3>Convenience Functions</h3>
    <table>
        <tr><th>Function</th><th>Description</th></tr>
        <tr><td><code>RangeI32(min, max)</code></td><td>Random i32 in range</td></tr>
        <tr><td><code>RangeU32(min, max)</code></td><td>Random u32 in range</td></tr>
        <tr><td><code>RangeF32(min, max)</code></td><td>Random f32 in range</td></tr>
        <tr><td><code>UnitF32()</code></td><td>Random f32 in [0,1]</td></tr>
        <tr><td><code>NormalF32(mean, stddev)</code></td><td>Normal distribution f32</td></tr>
        <tr><td><code>SignI32()</code></td><td>Random -1 or +1</td></tr>
        <tr><td><code>Boolean()</code></td><td>Random true/false</td></tr>
        <tr><td><code>Chance(probability)</code></td><td>True with given probability</td></tr>
        <tr><td><code>Index(size)</code></td><td>Random index for container</td></tr>
    </table>

    <h3>Container Random Selection</h3>
    <table>
        <tr><th>Function</th><th>Description</th></tr>
        <tr><td><code>Choice(container)</code></td><td>Random element from container</td></tr>
        <tr><td><code>Choice(begin, end)</code></td><td>Random element from iterator range</td></tr>
        <tr><td><code>Choice(initializer_list)</code></td><td>Random element from list</td></tr>
        <tr><td><code>WeightedChoice(values, weights)</code></td><td>Random element using weighted probabilities</td></tr>
        <tr><td><code>Shuffle(begin, end)</code></td><td>Randomly shuffle range</td></tr>
    </table>

    <h3>Example Usage</h3>
    <pre><code>// Basic random numbers

int randomInt = zen::random::RangeI32(0, 100);
float randomFloat = zen::random::RangeF32(-10.0f, 10.0f);
float unit = zen::random::UnitF32();

// Boolean and chance
if (zen::random::Boolean()) { /_ 50% chance _/ }
if (zen::random::Chance(0.75f)) { /_ 75% chance _/ }

// Random selection from containers
std::vector&lt;std::string&gt; names = {"Alice", "Bob", "Charlie"};
std::string& chosen = zen::random::Choice(names);

// Weighted random selection
std::vector&lt;float&gt; weights = {1.0f, 2.0f, 3.0f}; // Higher weight = higher probability
auto& weightedChoice = zen::random::WeightedChoice(names, weights);

// Shuffle
zen::random::Shuffle(names.begin(), names.end());</code></pre>

    <!-- Trigonometry Module -->
    <h2 id="trigonometry">Trigonometric Functions</h2>
    <p><code>#include &lt;zen/math/trigonometry.hpp&gt;</code></p>

    <h3>Overview</h3>
    <p>Trigonometric functions that work with the type-safe <code>Angle</code> type.</p>

    <h3>Functions</h3>
    <table>
        <tr><th>Function</th><th>Description</th></tr>
        <tr><td><code>Sin(Angle)</code></td><td>Sine of angle</td></tr>
        <tr><td><code>Cos(Angle)</code></td><td>Cosine of angle</td></tr>
        <tr><td><code>Tan(Angle)</code></td><td>Tangent of angle</td></tr>
        <tr><td><code>ArcSin(f32)</code></td><td>Angle from sine value</td></tr>
        <tr><td><code>ArcCos(f32)</code></td><td>Angle from cosine value</td></tr>
        <tr><td><code>ArcTan(f32)</code></td><td>Angle from tangent value</td></tr>
        <tr><td><code>ArcTan(Vec2f)</code></td><td>Angle from vector coordinates</td></tr>
    </table>

    <h3>Example Usage</h3>
    <pre><code>auto angle = zen::math::Angle::FromDegrees(45.0f);

float sine = zen::math::Sin(angle);
float cosine = zen::math::Cos(angle);

auto fromSin = zen::math::ArcSin(0.5f); // 30 degrees
auto fromVector = zen::math::ArcTan(zen::math::Vec2f{1.0f, 1.0f}); // 45 degrees</code></pre>

    <!-- Utils Module -->
    <h2 id="utils">Utility Functions</h2>
    <p><code>#include &lt;zen/math/utils.hpp&gt;</code></p>

    <h3>Overview</h3>
    <p>Collection of mathematical utility functions for common operations.</p>

    <h3>Comparison</h3>
    <table>
        <tr><th>Function</th><th>Description</th></tr>
        <tr><td><code>NearlyEqual(lhs, rhs, epsilon)</code></td><td>Floating-point approximate equality</td></tr>
    </table>

    <h3>Value Manipulation</h3>
    <table>
        <tr><th>Function</th><th>Description</th></tr>
        <tr><td><code>Clamp(value, min, max)</code></td><td>Constrain value between bounds</td></tr>
        <tr><td><code>Min(a, b)</code></td><td>Minimum of two values</td></tr>
        <tr><td><code>Max(a, b)</code></td><td>Maximum of two values</td></tr>
        <tr><td><code>Sign(value)</code></td><td>Returns -1, 0, or 1</td></tr>
    </table>

    <h3>Interpolation & Remapping</h3>
    <table>
        <tr><th>Function</th><th>Description</th></tr>
        <tr><td><code>Lerp(start, end, travel)</code></td><td>Linear interpolation</td></tr>
        <tr><td><code>InverseLerp(start, end, value)</code></td><td>Inverse interpolation factor</td></tr>
        <tr><td><code>Remap(value, inMin, inMax, outMin, outMax)</code></td><td>Remap value between ranges</td></tr>
        <tr><td><code>SmoothStep(edge0, edge1, value)</code></td><td>Hermite interpolation between edges</td></tr>
    </table>

    <h3>Wrapping & Repetition</h3>
    <table>
        <tr><th>Function</th><th>Description</th></tr>
        <tr><td><code>Wrap(value, min, max)</code></td><td>Wrap value into [min, max) range</td></tr>
        <tr><td><code>Repeat(value, length)</code></td><td>Repeat value within [0, length) interval</td></tr>
    </table>

    <h3>Example Usage</h3>
    <pre><code>// Clamping

float clamped = zen::math::Clamp(15.0f, 0.0f, 10.0f); // 10.0f

// Sign
int sign = zen::math::Sign(-42); // -1

// Interpolation
float lerped = zen::math::Lerp(0.0f, 100.0f, 0.5f); // 50.0f

// Remapping
float remapped = zen::math::Remap(0.5f, 0.0f, 1.0f, 0.0f, 100.0f); // 50.0f

// Wrapping
float wrapped = zen::math::Wrap(370.0f, 0.0f, 360.0f); // 10.0f

// Smooth step
float smooth = zen::math::SmoothStep(0.0f, 10.0f, 5.0f); // 0.5f with smooth curve</code></pre>

    <!-- Vec2 Module -->
    <h2 id="vec2">Vec2 - 2D Vector Mathematics</h2>
    <p><code>#include &lt;zen/math/vec2.hpp&gt;</code></p>

    <h3>Overview</h3>
    <p>Template-based 2D vector type with comprehensive mathematical operations. Supports both floating-point and integer components.</p>

    <h3>Type Aliases</h3>
    <table>
        <tr><th>Alias</th><th>Description</th></tr>
        <tr><td><code>Vec2f</code></td><td>Vec2&lt;f32&gt; - float vector</td></tr>
        <tr><td><code>Vec2i</code></td><td>Vec2&lt;i32&gt; - integer vector</td></tr>
    </table>

    <h3>Static Factory Methods</h3>
    <table>
        <tr><th>Method</th><th>Description</th></tr>
        <tr><td><code>Vec2::Zero()</code></td><td>(0, 0)</td></tr>
        <tr><td><code>Vec2::One()</code></td><td>(1, 1)</td></tr>
        <tr><td><code>Vec2::Up()</code></td><td>(0, 1)</td></tr>
        <tr><td><code>Vec2::Down()</code></td><td>(0, -1)</td></tr>
        <tr><td><code>Vec2::Left()</code></td><td>(-1, 0)</td></tr>
        <tr><td><code>Vec2::Right()</code></td><td>(1, 0)</td></tr>
        <tr><td><code>Vec2::Unit(value)</code></td><td>(value, value)</td></tr>
        <tr><td><code>Vec2::FromAngle(angle)</code></td><td>Unit vector from angle</td></tr>
    </table>

    <h3>Basic Operations</h3>
    <table>
        <tr><th>Method</th><th>Description</th></tr>
        <tr><td><code>Rotated90() / Rotated270()</code></td><td>Quick 90/270 degree rotation</td></tr>
        <tr><td><code>Rotated(angle)</code></td><td>Rotate by arbitrary angle</td></tr>
        <tr><td><code>Min(other) / Max(other)</code></td><td>Component-wise min/max</td></tr>
        <tr><td><code>Abs()</code></td><td>Absolute values</td></tr>
        <tr><td><code>Clamp(min, max)</code></td><td>Component-wise clamp</td></tr>
        <tr><td><code>Remap(inMin, inMax, outMin, outMax)</code></td><td>Component-wise remap</td></tr>
        <tr><td><code>Wrap(min, max)</code></td><td>Component-wise wrap</td></tr>
        <tr><td><code>SmoothStep(edge0, edge1)</code></td><td>Component-wise smooth step</td></tr>
    </table>

    <h3>Vector Operations</h3>
    <table>
        <tr><th>Method</th><th>Description</th></tr>
        <tr><td><code>Dot(other)</code></td><td>Dot product</td></tr>
        <tr><td><code>Cross(other)</code></td><td>2D cross product (scalar)</td></tr>
        <tr><td><code>Perpendicular()</code></td><td>Perpendicular vector (-y, x)</td></tr>
        <tr><td><code>LengthSquared()</code></td><td>Squared magnitude</td></tr>
        <tr><td><code>Length()</code></td><td>Magnitude</td></tr>
        <tr><td><code>LengthInverse()</code></td><td>1/length (or 0)</td></tr>
        <tr><td><code>DistanceSquared(other)</code></td><td>Squared distance</td></tr>
        <tr><td><code>Distance(other)</code></td><td>Distance</td></tr>
        <tr><td><code>Normalized()</code></td><td>Unit vector</td></tr>
    </table>

    <h3>Angular Operations</h3>
    <table>
        <tr><th>Method</th><th>Description</th></tr>
        <tr><td><code>AngleBetween(other)</code></td><td>Angle between vectors</td></tr>
        <tr><td><code>SignedAngle(other)</code></td><td>Signed angle (-π to π)</td></tr>
        <tr><td><code>GetAngle()</code></td><td>Polar angle of vector</td></tr>
    </table>

    <h3>Physics/Geometry Operations</h3>
    <table>
        <tr><th>Method</th><th>Description</th></tr>
        <tr><td><code>Reflect(normal)</code></td><td>Reflect off surface</td></tr>
        <tr><td><code>Project(other)</code></td><td>Project onto vector</td></tr>
        <tr><td><code>ClampLength(max)</code></td><td>Limit magnitude</td></tr>
        <tr><td><code>Lerp(start, end, travel)</code></td><td>Static linear interpolation</td></tr>
        <tr><td><code>SmoothDamp(target, smoothing)</code></td><td>Smooth movement towards target</td></tr>
        <tr><td><code>MoveTowards(target, maxDelta)</code></td><td>Move with max step</td></tr>
        <tr><td><code>Slide(normal)</code></td><td>Slide along surface</td></tr>
        <tr><td><code>Refract(normal, eta)</code></td><td>Refraction (Snell's law)</td></tr>
    </table>

    <h3>Operators</h3>
    <table>
        <tr><th>Operator</th><th>Description</th></tr>
        <tr><td><code>-</code></td><td>Negation</td></tr>
        <tr><td><code>+, -, *, /</code></td><td>Component-wise operations with vectors or scalars</td></tr>
        <tr><td><code>+=, -=, *=, /=</code></td><td>Compound assignment</td></tr>
        <tr><td><code>==, !=</code></td><td>Equality comparison</td></tr>
    </table>

    <h3>Free Functions</h3>
    <table>
        <tr><th>Function</th><th>Description</th></tr>
        <tr><td><code>DotProduct(lhs, rhs)</code></td><td>Dot product</td></tr>
        <tr><td><code>CrossProduct(lhs, rhs)</code></td><td>Cross product</td></tr>
        <tr><td><code>NearlyEqual(lhs, rhs, epsilon)</code></td><td>Approximate equality for float vectors</td></tr>
    </table>

    <h3>Example Usage</h3>
    <pre><code>// Creation

zen::math::Vec2f position(10.0f, 20.0f);
auto velocity = zen::math::Vec2f::Right() \* 5.0f; // (5, 0)

// Basic operations
position += velocity \* 0.016f; // Update position
float distance = position.Length();
float dot = position.Dot(velocity);

// Direction and rotation
auto direction = position.Normalized();
auto angle = position.GetAngle();
auto rotated = position.Rotated(zen::math::Angle::FromDegrees(90.0f));

// Interpolation
auto start = zen::math::Vec2f::Zero();
auto end = zen::math::Vec2f(100.0f, 100.0f);
auto mid = zen::math::Vec2f::Lerp(start, end, 0.5f); // (50, 50)

// Physics
auto normal = zen::math::Vec2f::Up();
auto reflection = velocity.Reflect(normal);
auto projection = velocity.Project(normal);

// Movement
auto current = zen::math::Vec2f(10.0f, 10.0f);
auto target = zen::math::Vec2f(20.0f, 20.0f);
auto moved = current.MoveTowards(target, 2.0f);</code></pre>

    <h2>Summary</h2>
    <p>The Zen Math Library provides a comprehensive set of mathematical tools including:</p>
    <ul>
        <li><strong>Angle</strong> - Type-safe angle representation with radian/degree conversion</li>
        <li><strong>Constants</strong> - Mathematical and numeric constants</li>
        <li><strong>Random</strong> - Random number generation with distributions and container selection</li>
        <li><strong>Trigonometry</strong> - Trigonometric functions integrated with Angle type</li>
        <li><strong>Utils</strong> - Common mathematical utilities</li>
        <li><strong>Vec2</strong> - Complete 2D vector mathematics</li>
    </ul>

    <div class="note">
        <strong>Note:</strong> All vector operations are optimized for performance while maintaining type safety. The library makes extensive use of compile-time checks and <code>constexpr</code> where possible.
    </div>

</body>
</html>>(ContainerT& container)`       | Constructs from mutable container      |
| `IteratorWrapper<>(const ContainerT& container)` | Constructs from const container        |

### Member Functions

| Function                                        | Description                                 | Complexity                             |
| ----------------------------------------------- | ------------------------------------------- | -------------------------------------- |
| `size_t GetSize() const noexcept`               | Returns number of elements in wrapped range | O(1)                                   |
| `IteratorT GetBegin() const noexcept`           | Returns begin iterator                      | O(1)                                   |
| `IteratorT GetEnd() const noexcept`             | Returns end iterator                        | O(1)                                   |
| `reference operator[](size_t index) const`      | Indexed access to elements                  | O(1) for random access, O(N) otherwise |
| `bool operator==(const IteratorWrapper&) const` | Equality comparison                         | O(1)                                   |
| `bool operator!=(const IteratorWrapper&) const` | Inequality comparison                       | O(1)                                   |
| `IteratorT begin() const noexcept`              | Range-based for support                     | O(1)                                   |
| `IteratorT end() const noexcept`                | Range-based for support                     | O(1)                                   |

### Deduction Guides

| Guide                                            | Purpose                |
| ------------------------------------------------ | ---------------------- |
| `IteratorWrapper(IteratorT, IteratorT)`          | For iterator pairs     |
| `IteratorWrapper<ContainerT>(ContainerT&)`       | For mutable containers |
| `IteratorWrapper<ContainerT>(const ContainerT&)` | For const containers   |

### Example Usage

```cpp
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // Create wrapper from container
    auto wrapper = zen::container::IteratorWrapper(numbers);

    // Use range-based for
    for (auto& num : wrapper) {
        num *= 2;
    }

    // Indexed access
    int third = wrapper[2];  // Returns 6

    // Create wrapper from iterator pair
    auto partial = zen::container::IteratorWrapper(
        numbers.begin() + 1,
        numbers.begin() + 4
    );
```

### Implementation Details

```cpp
    private:
        IteratorT _containerBegin; ///< Beginning iterator of the wrapped range.
        IteratorT _containerEnd;   ///< End iterator of the wrapped range.
        size_t    _containerSize;  ///< Cached size of the iterator range.
```

## ObjectPool

```cpp
    #include <zen/container/object_pool.hpp>
```

### `template<typename DataT> struct ObjectPool`

Fixed-size object pool that preallocates memory and provides O(N) acquisition/release of objects.
Uses a bitmap to track active slots, ideal for managing reusable objects in performance-critical code.

### Template Parameters

| Parameter | Description              |
| --------- | ------------------------ |
| `DataT`   | Type stored in the pool. |

### Constructors

| Constructor                           | Description                       |
| ------------------------------------- | --------------------------------- |
| `ObjectPool(size_t poolReserve = 64)` | Creates pool with fixed capacity. |

### Member Functions

| Function                                          | Description                                                             | Complexity |
| ------------------------------------------------- | ----------------------------------------------------------------------- | ---------- |
| `DataT* Acquire(Args&&... args)`                  | Acquires an inactive object and constructs it with the given arguments. | O(N)       |
| `void Release(DataT* objectPtr)`                  | Releases object back to pool                                            | O(1)       |
| `template<typename Fn> void ForEachActive(Fn fn)` | Iterates over all active objects                                        | O(N)       |
| `bool IsFull() const noexcept`                    | Checks if pool has reached capacity                                     | O(1)       |

### Memory Layout

- **`_objectBuffer`** : Contiguous storage for all objects (active and inactive)
- **`_objectActive`** : Boolean bitmap tracking which slots are in use
- **`_currentlyActive`** : Counter of currently active objects

### Example Usage

```cpp
    struct Particle {
        float x, y, z;
        float velocity;
        float lifetime;

        Particle(float x_, float y_, float z_, float vel_, float life_)
            : x(x_), y(y_), z(z_), velocity(vel_), lifetime(life_) {}
    };

    zen::container::ObjectPool<Particle> particlePool(1000);

    // Spawn particles
    for (int i = 0; i < 10; ++i) {
        Particle* p = particlePool.Acquire(
            rand() % 100, rand() % 100, 0.0f,
            1.0f,
            5.0f
        );
    }

    // Update all active particles
    particlePool.ForEachActive([](Particle& p) {
        p.x += p.velocity;
        p.lifetime -= 0.016f;
    });
```

### Implementation Details

```cpp
    private:
        std::vector<DataT> _objectBuffer; ///< Densely packed buffer of data
        std::vector<bool>  _objectActive; ///< Active flags of all data by index
        size_t _currentlyActive = 0;      ///< Number of active objects
```

## SparseSet

```cpp
    #include <zen/container/sparse_set.hpp>
```

### `template<typename DataT> struct SparseSet`

Sparse set container providing O(1) insertion, removal, and lookup by ID. Stores elements in a dense array while maintaining a sparse lookup table that maps external IDs to dense indices. Commonly used in Entity Component Systems (ECS) where entities are sparse but components must be iterated efficiently.

### Template Parameters

| Parameter | Description                            |
| --------- | -------------------------------------- |
| `DataT`   | Type of data stored in the sparse set. |

### Private Types

| Type       | Description                              |
| ---------- | ---------------------------------------- |
| `DataRef`  | Mutable reference to data (`DataT&`)     |
| `CDataRef` | Const reference to data (`const DataT&`) |

### Constructors

| Constructor                                                      | Description                                                                      |
| ---------------------------------------------------------------- | -------------------------------------------------------------------------------- |
| `SparseSet(size_t sparseReserve = 64, size_t denseReserve = 64)` | Constructs a sparse set with reserved capacity for both sparse and dense arrays. |

### Member Functions

| Function                                           | Description                                    | Complexity     |
| -------------------------------------------------- | ---------------------------------------------- | -------------- |
| `void Insert(size_t id, DataT value)`              | Inserts a value associated with an ID          | O(1) amortized |
| `void Remove(size_t dataID)`                       | Removes the value associated with an ID        | O(1)           |
| `bool Contains(size_t dataID) const noexcept`      | Checks if an ID exists in the sparse set       | O(1)           |
| `const std::vector<DataT>& Dense() const noexcept` | Returns the dense storage buffer for iteration | O(1)           |
| `size_t Size() const noexcept`                     | Returns the number of stored elements          | O(1)           |
| `DataRef operator[](size_t dataID)`                | Access data by ID (mutable)                    | O(1)           |
| `CDataRef operator[](size_t dataID) const`         | Access data by ID (const)                      | O(1)           |

### Memory Layout

- **`_sparseIDs`** : Maps external IDs → dense indices
- **`_denseIDs`** : Maps dense indices → external IDs
- **`_denseData`** : Contiguous storage of data values

### How It Works

The sparse set maintains two parallel arrays:

1. **Sparse array** : Indexed by external ID, stores position in dense array
2. **Dense array** : Stores elements contiguously for fast iteration

When an element is removed, the last element in the dense array is moved into its place, and the sparse mapping is updated accordingly.

### Example Usage

```cpp
    // Component type for ECS
    struct TransformComponent {
        float x, y, z;
        float rotation;
        float scale;
    };

    zen::container::SparseSet<TransformComponent> transforms;

    // Add components to entities
    transforms.Insert(42, TransformComponent{0, 0, 0, 0, 1});
    transforms.Insert(17, TransformComponent{10, 20, 0, 90, 1});
    transforms.Insert(93, TransformComponent{-5, 15, 0, 45, 2});

    // Check if entity has component
    if (transforms.Contains(42)) {
        // Access component directly
        auto& transform = transforms[42];
        transform.x += 5;
    }

    // Fast iteration over all components
    for (const auto& component : transforms.Dense()) {
        renderTransform(component);
    }

    // Remove component
    transforms.Remove(17);

    // Size reflects only active components
    std::cout << "Active transforms: " << transforms.Size() << "\n";  // Output: 2
```

### Implementation Details

```cpp
    private:
        std::vector<size_t> _sparseIDs; ///< Maps external IDs → dense indices
        std::vector<size_t> _denseIDs;  ///< Maps dense indices → external IDs
        std::vector<DataT>  _denseData; ///< Contiguous storage of data
```

### Performance Characteristics

| Operation | Complexity     | Notes                          |
| --------- | -------------- | ------------------------------ |
| Insert    | O(1) amortized | May resize sparse array        |
| Remove    | O(1)           | Swaps with last element        |
| Lookup    | O(1)           | Direct index into sparse array |
| Iteration | O(N)           | Cache-friendly dense traversal |
| Memory    | O(S + D)       | S = max ID, D = active count   |

## Summary

| Container            | Best For                | Lookup   | Insert | Remove | Iteration | Memory   |
| -------------------- | ----------------------- | -------- | ------ | ------ | --------- | -------- |
| **DoubleBuffer**     | Staged data exchange    | O(1)     | N/A    | N/A    | O(1)      | O(2)     |
| **FastAccessBuffer** | Sorted ID-based storage | O(log N) | O(N)   | O(N)   | O(N)      | O(N)     |
| **IteratorWrapper**  | Range abstraction       | O(1)\*   | N/A    | N/A    | O(N)      | O(1)     |
| **ObjectPool**       | Object reuse            | N/A      | O(N)   | O(1)   | O(N)      | O(N)     |
| **SparseSet**        | ECS components          | O(1)     | O(1)   | O(1)   | O(N)      | O(S + D) |

\*For random access iterators only
