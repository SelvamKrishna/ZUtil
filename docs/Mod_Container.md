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

| Constructor                                                | Description                            |
| ---------------------------------------------------------- | -------------------------------------- |
| `IteratorWrapper(IteratorT itBegin, IteratorT itEnd)`      | Constructs from explicit iterator pair |
| `IteratorWrapper<ContainerT>(ContainerT& container)`       | Constructs from mutable container      |
| `IteratorWrapper<ContainerT>(const ContainerT& container)` | Constructs from const container        |

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
