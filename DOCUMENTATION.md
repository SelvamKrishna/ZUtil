# Zen Utility Library

---

## Zen Container Module

Specialized data structures for high-performance C++ applications.

### `DoubleBuffer<DataT>`

Two buffers: one for reading, one for writing. Swap to publish changes.

Method | Description
---|---
`DoubleBuffer(readVal, writeVal)` | Create with initial values
`Read()` | Get read buffer (const)
`Write()` | Get write buffer (mutable)
`Swap()` | Exchange read/write buffers

```cpp
    zen::container::DoubleBuffer<Transform> transBuf;
    auto& w = transBuf.Write();      // modify
    transBuf.Swap();                 // publish
    const auto& r = transBuf.Read(); // use
```

### `FastAccessBuffer<DataT>`

ID-based storage with binary search (O(log N)). Sorted by ID.

Method | Description
---|---
`FastAccessBuffer(reserve = 32)` | Create with capacity
`Insert(data)` | Add data, returns new ID
`Remove(id)` | Remove by ID
`Contains(id)` | Check if ID exists
`operator[](id)` | Access by ID
`Size()` | Number of elements

```cpp
    zen::container::FastAccessBuffer<Player> buf;
    size_t id = buf.Insert(Player{"Alice"});
    if (buf.Contains(id)) buf[id].health = 100;
```

### `IteratorWrapper<IteratorT>`

Wraps iterator pairs into a single object with size and indexing.

Method | Description
---|---
`IteratorWrapper(begin, end)` | From iterator pair
`IteratorWrapper(container)` | From container
`GetSize()` | Number of elements
`operator[](i)` | Index access

```cpp
    vector<int> v = {1,2,3,4,5};
    auto wrap = zen::container::IteratorWrapper(v);
    for (auto& x : wrap) x *= 2;
    int third = wrap[2];
```

### `ObjectPool<DataT>`

Fixed-size pool with active/inactive tracking.

Method | Description
---|---
`ObjectPool(size = 64)` | Create pool
`Acquire(args...)` | Get object or nullptr
`Release(ptr)` | Return to pool
`ForEachActive(fn)` | Iterate active
`IsFull()` | Pool at capacity?

```cpp
    zen::container::ObjectPool<Particle> pool(1000);
    Particle* p = pool.Acquire(0,0,0,1,5.0f);
    pool.ForEachActive([](Particle& p) { p.update(); });
    pool.Release(p);
```

### `SparseSet<DataT>`

O(1) lookup by ID, dense storage for fast iteration. Perfect for ECS.

Method | Description
---|---
`SparseSet(sparseCap, denseCap)` | Create with capacity
`Insert(id, value)` | Add with external ID
`Remove(id)` | Remove by ID
`Contains(id)` | Check existence
`Dense()` | Get dense array
`operator[](id)` | Access by ID
`Size()` | Active count

```cpp
    zen::container::SparseSet<Transform> transforms;
    transforms.Insert(42, Transform{0,0,0});
    auto& t = transforms[42];  // O(1)
    for (auto& comp : transforms.Dense()) { /* fast iteration */ }
    transforms.Remove(42);
```

### Quick Reference

Container | Best For | Lookup | Insert | Remove
---|---|---|---|---
`DoubleBuffer` | Thread-safe sharing | O(1) | - | -
`FastAccessBuffer` | Sorted ID storage | O(log N) | O(N) | O(N)
`IteratorWrapper` | Range abstraction | O(1)* | - | -
`ObjectPool` | Object reuse | - | O(N) | O(1)
`SparseSet` | ECS components | O(1) | O(1) | O(1)
