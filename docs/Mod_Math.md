# Zen Math Library Documentation

## Module (`zen::math`), (`zen::random`)

### Table of Contents

1. [Angle - Type-Safe Angle Representation](#angle---type-safe-angle-representation)
2. [Mathematical Constants](#mathematical-constants)
3. [Random Number Generation](#random-number-generation)
4. [Trigonometric Functions](#trigonometric-functions)
5. [Utility Functions](#utility-functions)
6. [Vec2 - 2D Vector Mathematics](#vec2---2d-vector-mathematics)

## Angle - Type-Safe Angle Representation

`#include <zen/math/angle.hpp>`

### Overview

The `Angle` type provides a type-safe abstraction over raw floating-point values when working with rotations or angular measurements. Angles are stored internally in radians (f32) but can be created from and converted to degrees.

### Conversion Functions

| Function                        | Description                 |
| ------------------------------- | --------------------------- |
| `DegreesToRadians(f32 degrees)` | Converts degrees to radians |
| `RadiansToDegrees(f32 radians)` | Converts radians to degrees |

### Static Factory Methods

| Method                            | Description                |
| --------------------------------- | -------------------------- |
| `Angle::FromRadians(f32 radians)` | Creates angle from radians |
| `Angle::FromDegrees(f32 degrees)` | Creates angle from degrees |

### Member Functions

| Function       | Description                         |
| -------------- | ----------------------------------- |
| `AsRadians()`  | Returns angle in radians            |
| `AsDegrees()`  | Returns angle in degrees            |
| `Normalized()` | Returns angle normalized to [0, 2π) |
| `Sin()`        | Computes sine of the angle          |
| `Cos()`        | Computes cosine of the angle        |
| `Tan()`        | Computes tangent of the angle       |

### Operators

| Operator               | Description                                   |
| ---------------------- | --------------------------------------------- |
| `+, -, *, /`           | Arithmetic operations                         |
| `+=, -=`               | Compound assignment                           |
| `==, !=, <, >, <=, >=` | Comparison operators (with epsilon tolerance) |

### Example Usage

```cpp
    // Create angles
    auto rightAngle = zen::math::Angle::FromDegrees(90.0f);
    auto piAngle = zen::math::Angle::FromRadians(zen::math::constants::F32_PI);

    // Conversions
    float degrees = rightAngle.AsDegrees();  // 90.0f
    float radians = rightAngle.AsRadians();  // π/2

    // Trigonometric functions
    float sinVal = rightAngle.Sin();  // 1.0f
    float cosVal = rightAngle.Cos();  // 0.0f

    // Normalization
    auto largeAngle = zen::math::Angle::FromDegrees(450.0f);
    auto normalized = largeAngle.Normalized();  // 90 degrees

    // Arithmetic
    auto sum = rightAngle + piAngle;
    auto doubled = rightAngle * 2.0f;
```

## Mathematical Constants

`#include <zen/math/constants.hpp>`

### Overview

Comprehensive set of mathematical and numeric constants for both 32-bit and 64-bit types.

### Integer Limits

| Signed               | Unsigned  |
| -------------------- | --------- |
| `I8_MIN` , `I8_MAX`  | `U8_MAX`  |
| `I16_MIN`, `I16_MAX` | `U16_MAX` |
| `I32_MIN`, `I32_MAX` | `U32_MAX` |
| `I64_MIN`, `I64_MAX` | `U64_MAX` |

### Floating Point Limits

| 32-bit                | 64-bit                | Description                     |
| --------------------- | --------------------- | ------------------------------- |
| `F32_MIN`             | `F64_MIN`             | Minimum positive normal         |
| `F32_LOWEST`          | `F64_LOWEST`          | Most negative finite value      |
| `F32_MAX`             | `F64_MAX`             | Maximum finite value            |
| `F32_EPSILON`         | `F64_EPSILON`         | Machine epsilon                 |
| `F32_COMPARE_EPSILON` | `F64_COMPARE_EPSILON` | 1e-4f (comparison tolerance)    |
| `F32_NORMAL_EPSILON`  | `F64_NORMAL_EPSILON`  | 1e-8f (normalization tolerance) |
| `F32_INFINITY`        | `F64_INFINITY`        | Positive infinity               |
| `F32_NEG_INFINITY`    | `F64_NEG_INFINITY`    | Negative infinity               |

### Mathematical Constants

| 32-bit             | 64-bit             | Description    |
| ------------------ | ------------------ | -------------- |
| `F32_PI`           | `F64_PI`           | π (3.14159...) |
| `F32_TWO_PI`       | `F64_TWO_PI`       | 2π             |
| `F32_TAU`          | `F64_TAU`          | τ (2π) - alias |
| `F32_HALF_PI`      | `F64_HALF_PI`      | π/2            |
| `F32_INV_PI`       | `F64_INV_PI`       | 1/π            |
| `F32_GOLDEN_RATIO` | `F64_GOLDEN_RATIO` | φ (1.61803...) |

## Random Number Generation

`#include <zen/math/random.hpp>`

### Overview

Comprehensive random number generation utilities with support for various distributions and container-based random selection.

### Global Engine Control

| Function             | Description                                         |
| -------------------- | --------------------------------------------------- |
| `GetEngine()`        | Returns reference to global Mersenne Twister engine |
| `GenerateSeed()`     | Generates random seed using system entropy          |
| `SetSeed(u32 value)` | Seeds the global random engine                      |

### Distribution Templates

| Function                                     | Description                                          |
| -------------------------------------------- | ---------------------------------------------------- |
| `UniformDistribution<NumericT>(min, max)`    | Uniform distribution (integral or floating-point)    |
| `NormalDistribution<NumericT>(mean, stddev)` | Normal (Gaussian) distribution                       |
| `DiscreteDistribution(weights)`              | Weighted discrete distribution using IteratorWrapper |

### Convenience Functions

| Function                  | Description                 |
| ------------------------- | --------------------------- |
| `RangeI32(min, max)`      | Random i32 in range         |
| `RangeU32(min, max)`      | Random u32 in range         |
| `RangeF32(min, max)`      | Random f32 in range         |
| `UnitF32()`               | Random f32 in [0,1]         |
| `NormalF32(mean, stddev)` | Normal distribution f32     |
| `SignI32()`               | Random -1 or +1             |
| `Boolean()`               | Random true/false           |
| `Chance(probability)`     | True with given probability |
| `Index(size)`             | Random index for container  |

### Container Random Selection

| Function                          | Description                                 |
| --------------------------------- | ------------------------------------------- |
| `Choice(container)`               | Random element from container               |
| `Choice(begin, end)`              | Random element from iterator range          |
| `Choice(initializer_list)`        | Random element from list                    |
| `WeightedChoice(values, weights)` | Random element using weighted probabilities |
| `Shuffle(begin, end)`             | Randomly shuffle range                      |

### Example Usage

```cpp
    // Basic random numbers
    int randomInt = zen::random::RangeI32(0, 100);
    float randomFloat = zen::random::RangeF32(-10.0f, 10.0f);
    float unit = zen::random::UnitF32();

    // Boolean and chance
    if (zen::random::Boolean()) { /* 50% chance */ }
    if (zen::random::Chance(0.75f)) { /* 75% chance */ }

    // Random selection from containers
    std::vector<std::string> names = {"Alice", "Bob", "Charlie"};
    std::string& chosen = zen::random::Choice(names);

    // Weighted random selection
    std::vector<float> weights = {1.0f, 2.0f, 3.0f};  // Higher weight = higher probability
    auto& weightedChoice = zen::random::WeightedChoice(names, weights);

    // Shuffle
    zen::random::Shuffle(names.begin(), names.end());
```

## Trigonometric Functions

`#include <zen/math/trigonometry.hpp>`

### Overview

Trigonometric functions that work with the type-safe `Angle` type.

### Functions

| Function        | Description                   |
| --------------- | ----------------------------- |
| `Sin(Angle)`    | Sine of angle                 |
| `Cos(Angle)`    | Cosine of angle               |
| `Tan(Angle)`    | Tangent of angle              |
| `ArcSin(f32)`   | Angle from sine value         |
| `ArcCos(f32)`   | Angle from cosine value       |
| `ArcTan(f32)`   | Angle from tangent value      |
| `ArcTan(Vec2f)` | Angle from vector coordinates |

### Example Usage

```cpp
    auto angle = zen::math::Angle::FromDegrees(45.0f);
    float sine = zen::math::Sin(angle);
    float cosine = zen::math::Cos(angle);

    auto fromSin = zen::math::ArcSin(0.5f);  // 30 degrees
    auto fromVector = zen::math::ArcTan(zen::math::Vec2f{1.0f, 1.0f});  // 45 degrees
```

## Utility Functions

`#include <zen/math/utils.hpp>`

### Overview

Collection of mathematical utility functions for common operations.

### Comparison

| Function                         | Description                         |
| -------------------------------- | ----------------------------------- |
| `NearlyEqual(lhs, rhs, epsilon)` | Floating-point approximate equality |

### Value Manipulation

| Function                 | Description                    |
| ------------------------ | ------------------------------ |
| `Clamp(value, min, max)` | Constrain value between bounds |
| `Min(a, b)`              | Minimum of two values          |
| `Max(a, b)`              | Maximum of two values          |
| `Sign(value)`            | Returns -1, 0, or 1            |

### Interpolation & Remapping

| Function                                     | Description                         |
| -------------------------------------------- | ----------------------------------- |
| `Lerp(start, end, travel)`                   | Linear interpolation                |
| `InverseLerp(start, end, value)`             | Inverse interpolation factor        |
| `Remap(value, inMin, inMax, outMin, outMax)` | Remap value between ranges          |
| `SmoothStep(edge0, edge1, value)`            | Hermite interpolation between edges |

### Wrapping & Repetition

| Function                | Description                              |
| ----------------------- | ---------------------------------------- |
| `Wrap(value, min, max)` | Wrap value into (min, max) range         |
| `Repeat(value, length)` | Repeat value within (0, length) interval |

### Example Usage

```cpp
    // Clamping
    float clamped = zen::math::Clamp(15.0f, 0.0f, 10.0f);  // 10.0f

    // Sign
    int sign = zen::math::Sign(-42);  // -1

    // Interpolation
    float lerped = zen::math::Lerp(0.0f, 100.0f, 0.5f);  // 50.0f

    // Remapping
    float remapped = zen::math::Remap(0.5f, 0.0f, 1.0f, 0.0f, 100.0f);  // 50.0f

    // Wrapping
    float wrapped = zen::math::Wrap(370.0f, 0.0f, 360.0f);  // 10.0f

    // Smooth step
    float smooth = zen::math::SmoothStep(0.0f, 10.0f, 5.0f);  // 0.5f with smooth curve
```

## Vec2 - 2D Vector Mathematics

`#include <zen/math/vec2.hpp>`

### Overview

Template-based 2D vector type with comprehensive mathematical operations. Supports both floating-point and integer components.

### Type Aliases

| Alias   | Description                |
| ------- | -------------------------- |
| `Vec2f` | Vec2<f32> - float vector   |
| `Vec2i` | Vec2<i32> - integer vector |

### Static Factory Methods

| Method                   | Description            |
| ------------------------ | ---------------------- |
| `Vec2::Zero()`           | (0, 0)                 |
| `Vec2::One()`            | (1, 1)                 |
| `Vec2::Up()`             | (0, 1)                 |
| `Vec2::Down()`           | (0, -1)                |
| `Vec2::Left()`           | (-1, 0)                |
| `Vec2::Right()`          | (1, 0)                 |
| `Vec2::Unit(value)`      | (value, value)         |
| `Vec2::FromAngle(angle)` | Unit vector from angle |

### Basic Operations

| Method                                | Description                  |
| ------------------------------------- | ---------------------------- |
| `Rotated90() / Rotated270()`          | Quick 90/270 degree rotation |
| `Rotated(angle)`                      | Rotate by arbitrary angle    |
| `Min(other) / Max(other)`             | Component-wise min/max       |
| `Abs()`                               | Absolute values              |
| `Clamp(min, max)`                     | Component-wise clamp         |
| `Remap(inMin, inMax, outMin, outMax)` | Component-wise remap         |
| `Wrap(min, max)`                      | Component-wise wrap          |
| `SmoothStep(edge0, edge1)`            | Component-wise smooth step   |

### Vector Operations

| Method                   | Description                             |
| ------------------------ | --------------------------------------- |
| `Dot(other)`             | Dot product _x1y1 + x2y2_               |
| `Cross(other)`           | 2D cross product (scalar) _x1y2 - x2y1_ |
| `Perpendicular()`        | Perpendicular vector (-y, x)            |
| `LengthSquared()`        | Squared magnitude                       |
| `Length()`               | Magnitude                               |
| `LengthInverse()`        | 1/length (or 0)                         |
| `DistanceSquared(other)` | Squared distance                        |
| `Distance(other)`        | Distance                                |
| `Normalized()`           | Unit vector                             |

### Angular Operations

| Method                | Description            |
| --------------------- | ---------------------- |
| `AngleBetween(other)` | Angle between vectors  |
| `SignedAngle(other)`  | Signed angle (-π to π) |
| `GetAngle()`          | Polar angle of vector  |

### Physics/Geometry Operations

| Method                          | Description                    |
| ------------------------------- | ------------------------------ |
| `Reflect(normal)`               | Reflect off surface            |
| `Project(other)`                | Project onto vector            |
| `ClampLength(max)`              | Limit magnitude                |
| `Lerp(start, end, travel)`      | Static linear interpolation    |
| `SmoothDamp(target, smoothing)` | Smooth movement towards target |
| `MoveTowards(target, maxDelta)` | Move with max step             |
| `Slide(normal)`                 | Slide along surface            |
| `Refract(normal, eta)`          | Refraction (Snell's law)       |

### Operators

| Operator         | Description                                       |
| ---------------- | ------------------------------------------------- |
| `-`              | Negation                                          |
| `+, -, *, /`     | Component-wise operations with vectors or scalars |
| `+=, -=, *=, /=` | Compound assignment                               |
| `==, !=`         | Equality comparison                               |

### Free Functions

| Function                         | Description                            |
| -------------------------------- | -------------------------------------- |
| `DotProduct(lhs, rhs)`           | Dot product                            |
| `CrossProduct(lhs, rhs)`         | Cross product                          |
| `NearlyEqual(lhs, rhs, epsilon)` | Approximate equality for float vectors |

### Example Usage

```cpp
    // Creation
    zen::math::Vec2f position(10.0f, 20.0f);
    auto velocity = zen::math::Vec2f::Right() * 5.0f;  // (5, 0)

    // Basic operations
    position += velocity * 0.016f;  // Update position
    float distance = position.Length();
    float dot = position.Dot(velocity);

    // Direction and rotation
    auto direction = position.Normalized();
    auto angle = position.GetAngle();
    auto rotated = position.Rotated(zen::math::Angle::FromDegrees(90.0f));

    // Interpolation
    auto start = zen::math::Vec2f::Zero();
    auto end = zen::math::Vec2f(100.0f, 100.0f);
    auto mid = zen::math::Vec2f::Lerp(start, end, 0.5f);  // (50, 50)

    // Physics
    auto normal = zen::math::Vec2f::Up();
    auto reflection = velocity.Reflect(normal);
    auto projection = velocity.Project(normal);

    // Movement
    auto current = zen::math::Vec2f(10.0f, 10.0f);
    auto target = zen::math::Vec2f(20.0f, 20.0f);
    auto moved = current.MoveTowards(target, 2.0f);
```

## Summary

The Zen Math Library provides a comprehensive set of mathematical tools including:

- **Angle** - Type-safe angle representation with radian/degree conversion
- **Constants** - Mathematical and numeric constants
- **Random** - Random number generation with distributions and container selection
- **Trigonometry** - Trigonometric functions integrated with Angle type
- **Utils** - Common mathematical utilities
- **Vec2** - Complete 2D vector mathematics

**Note:** All vector operations are optimized for performance while maintaining
type safety. The library makes extensive use of compile-time checks and
`constexpr` where possible.
