# CPP_08/ex01 — Span Class: Complete Explanation

---

## Part 1: Concepts & Containers Used

### 1. `std::vector<int>` — The Dynamic Array

`std::vector` is the **most commonly used container** in C++. It stores elements in a **contiguous block of memory** (just like a C-style array), but it can **grow dynamically**.

#### How it works under the hood

```
Heap memory layout of a vector with size=3, capacity=4:

_data pointer → [ 6 | 3 | 17 |   ]
                  ^              ^
                  begin()        end() points HERE (one past the last element)
                                 The 4th slot exists but is unused (capacity)
```

A `std::vector` internally holds **3 things**:
1. **A pointer** to a heap-allocated array (`_data`)
2. **Size** — how many elements are currently stored
3. **Capacity** — how many elements the allocated block can hold *before* it needs to reallocate

#### Key operations used in this code

| Operation | What it does | Time Complexity |
|-----------|-------------|-----------------|
| `push_back(x)` | Adds `x` to the end. If `size == capacity`, it **allocates a new block** (usually 2× the old capacity), **copies** all existing elements, and **frees** the old block. | Amortized O(1) |
| `size()` | Returns the number of elements | O(1) |
| `begin()` / `end()` | Returns iterators to the first element and one-past-the-last | O(1) |
| `operator[]` | Direct access by index (no bounds checking) | O(1) |

#### Reallocation in detail

When you `push_back` and the vector is full:
```
Before (size=4, capacity=4):
[ 6 | 3 | 17 | 9 ]

push_back(11) triggers reallocation:

1. Allocate new block of capacity 8:
   [ _ | _ | _ | _ | _ | _ | _ | _ ]

2. Copy old elements:
   [ 6 | 3 | 17 | 9 | _ | _ | _ | _ ]

3. Add new element:
   [ 6 | 3 | 17 | 9 | 11 | _ | _ | _ ]

4. Free old block
   Now size=5, capacity=8
```

The growth factor is implementation-defined but is typically **2×** (GCC/libstdc++) or **1.5×** (MSVC). This gives `push_back` an **amortized O(1)** cost — most calls are O(1), but occasionally one is O(n) for the copy. Averaged out, it's still O(1) per insertion.

#### Why contiguous memory matters

Because elements sit next to each other in RAM, the CPU can predict which memory you'll access next and preload it into the **cache** (cache-friendly). This makes `std::vector` extremely fast for sequential access compared to `std::list`.

---

### 2. `std::list<int>` — The Doubly-Linked List

`std::list` stores each element in a **separate heap-allocated node**, where each node has pointers to the **previous and next** node.

#### How it works under the hood

```
std::list<int> with elements {5, 3, 17, 9}:

  HEAD                                                 TAIL
   ↓                                                    ↓
[prev|5|next] ⟷ [prev|3|next] ⟷ [prev|17|next] ⟷ [prev|9|next]
  ↑ nullptr                                       nullptr ↑
```

Each node is a struct like:
```cpp
struct Node {
    int   data;
    Node* prev;
    Node* next;
};
```

| Operation | Vector | List |
|-----------|--------|------|
| Random access `[i]` | O(1) ✅ | O(n) ❌ (must walk the chain) |
| `push_back` | Amortized O(1) | O(1) always |
| Insert in the middle | O(n) (shift elements) | O(1) if you have an iterator |
| Cache friendliness | Excellent (contiguous) | Poor (nodes scattered in heap) |
| Memory overhead | Low (just the data) | High (2 pointers per node) |

In this code, `std::list` is used in `main()` **only to demonstrate** that `addRange` works with different container types — it proves the template accepts any iterator, not just vector iterators.

---

### 3. Iterators — The Abstraction Layer

An iterator is an **object that behaves like a pointer**. It lets you traverse a container without knowing the container's internal structure.

#### Iterator categories (relevant here)

| Category | Can do | Example containers |
|----------|--------|--------------------|
| **Input Iterator** | Read, move forward (`++`, `*`, `!=`) | `std::istream_iterator` |
| **Bidirectional Iterator** | Input + move backward (`--`) | `std::list` |
| **Random Access Iterator** | Bidirectional + jump (`+n`, `-n`, `[]`, `<`) | `std::vector`, raw pointers |

When you write `v.begin()`, the vector returns a **random access iterator** (essentially a wrapped pointer to `&v[0]`). When you write `lst.begin()`, the list returns a **bidirectional iterator** (a wrapped pointer to the first node).

The `addRange` template accepts `InputIterator` — the **weakest** category. Since bidirectional and random-access iterators are **supersets** of input iterators, they all work. That's why both `v.begin()` and `lst.begin()` can be passed to `addRange`.

#### How `++it` works differently

- **Vector iterator**: Increment the internal pointer by `sizeof(int)` — just pointer arithmetic. Fast.
- **List iterator**: Follow the `next` pointer in the current node to reach the next node. Requires a memory dereference (potentially a cache miss).

---

### 4. Templates — Compile-Time Polymorphism

```cpp
template <typename InputIterator>
void Span::addRange(InputIterator begin, InputIterator end);
```

A template is **not a function** — it's a **blueprint**. The compiler generates a **separate, specialized function** for each type you use it with. When main.cpp calls:

```cpp
sp.addRange(v.begin(), v.end());   // v is a std::vector<int>
sp.addRange(lst.begin(), lst.end()); // lst is a std::list<int>
```

The compiler generates **two different functions**:
```cpp
// Generated for vector:
void Span::addRange(std::vector<int>::iterator begin, std::vector<int>::iterator end);

// Generated for list:
void Span::addRange(std::list<int>::iterator begin, std::list<int>::iterator end);
```

This happens at **compile time** — there's zero runtime overhead. This is called **monomorphization** or **static dispatch**.

> **Why is the template defined in the header?**
> Because the compiler needs to see the template body at every translation unit (`.cpp` file) where it's used. If you put it in `Span.cpp`, the compiler wouldn't know how to generate the specialization when compiling `main.cpp`. That's why template definitions **must** be in headers.

---

### 5. The Orthodox Canonical Form (OCF)

The class implements all 4 special member functions required by the C++98 42 norm:

| Function | Purpose |
|----------|---------|
| **Default constructor** `Span()` | Creates a Span with `_maxSize = 0` |
| **Copy constructor** `Span(const Span&)` | Deep-copies another Span (vector's copy constructor handles the deep copy of elements) |
| **Copy assignment operator** `operator=` | Assigns from another Span with self-assignment check |
| **Destructor** `~Span()` | Cleanup (vector's destructor automatically frees its heap memory) |

---

### 6. Custom Exceptions

```cpp
class SpanFullException : public std::exception {
public:
    const char* what() const throw();
};
```

- Inherits from `std::exception`, so it can be caught by `catch (std::exception& e)`
- Overrides `what()` to return a descriptive C-string
- `throw()` is an **exception specification** (C++98) meaning "this function promises not to throw". In C++11+ this becomes `noexcept`.

---

### 7. STL Algorithms Used

| Algorithm | What it does | Complexity |
|-----------|-------------|------------|
| `std::sort(begin, end)` | Sorts the range in-place (typically introsort: quicksort + heapsort + insertion sort hybrid) | O(n log n) |
| `std::min_element(begin, end)` | Returns iterator to the smallest element | O(n) |
| `std::max_element(begin, end)` | Returns iterator to the largest element | O(n) |

`std::sort` requires **random access iterators** (that's why it works on vectors but NOT on lists — lists have their own `lst.sort()` member function).

---

## Part 2: Line-by-Line Execution Flow

### Test 1: Subject Test (lines 8–20)

```cpp
std::cout << "=== Subject test ===" << std::endl;
```
**Output:** `=== Subject test ===`

```cpp
Span sp = Span(5);
```
1. `Span(5)` is called → `_maxSize = 5`, `_numbers` is an empty vector (size=0, capacity=0)
2. This temporary is **copy-constructed** into `sp` (though the compiler will likely **elide** the copy entirely via RVO — Return Value Optimization)

```cpp
sp.addNumber(6);
```
- `_numbers.size()` is 0, `_maxSize` is 5 → 0 < 5, no exception
- `_numbers.push_back(6)` → vector allocates memory (typical initial capacity=1), stores 6
- Vector state: `[6]`, size=1

```cpp
sp.addNumber(3);
```
- size=1 < 5, OK
- `push_back(3)` → capacity was 1, need to reallocate to 2, copy 6, add 3
- Vector state: `[6, 3]`, size=2

```cpp
sp.addNumber(17);
```
- size=2 < 5, OK
- `push_back(17)` → capacity was 2, reallocate to 4, copy [6,3], add 17
- Vector state: `[6, 3, 17]`, size=3

```cpp
sp.addNumber(9);
```
- size=3 < 5, OK, capacity is 4, no reallocation needed
- Vector state: `[6, 3, 17, 9]`, size=4

```cpp
sp.addNumber(11);
```
- size=4 < 5, OK
- `push_back(11)` → capacity was 4, reallocate to 8, copy [6,3,17,9], add 11
- Vector state: `[6, 3, 17, 9, 11]`, size=5

```cpp
std::cout << sp.shortestSpan() << std::endl;
```

Inside `shortestSpan()`:
1. `_numbers.size()` is 5 ≥ 2, no exception
2. Create a **copy** of `_numbers`: `sorted = [6, 3, 17, 9, 11]`
3. `std::sort(sorted.begin(), sorted.end())` →  `sorted = [3, 6, 9, 11, 17]`
4. `minSpan = sorted[1] - sorted[0] = 6 - 3 = 3`
5. Loop:
   - i=2: `diff = 9 - 6 = 3`, 3 is not < 3, no change
   - i=3: `diff = 11 - 9 = 2`, 2 < 3, `minSpan = 2`
   - i=4: `diff = 17 - 11 = 6`, 6 is not < 2, no change
6. Return `2`

**Output:** `2`

```cpp
std::cout << sp.longestSpan() << std::endl;
```

Inside `longestSpan()`:
1. Size 5 ≥ 2, no exception
2. `min = *std::min_element(...)` → scans [6,3,17,9,11], finds 3
3. `max = *std::max_element(...)` → scans [6,3,17,9,11], finds 17
4. Return `17 - 3 = 14`

**Output:** `14`

The `}` at line 20 destroys `sp` → `_numbers`'s destructor frees the heap memory.

---

### Test 2: Span Full Exception (lines 22–33)

```cpp
Span sp(3);
```
`_maxSize = 3`, empty vector.

```cpp
sp.addNumber(1);  // size 0 < 3 → OK, vector: [1]
sp.addNumber(2);  // size 1 < 3 → OK, vector: [1, 2]
sp.addNumber(3);  // size 2 < 3 → OK, vector: [1, 2, 3]
sp.addNumber(4);  // size 3 >= 3 → THROWS SpanFullException!
```

The `throw SpanFullException()` creates an exception object. **Stack unwinding** begins:
- The call stack unwinds back to the nearest matching `catch` block
- No local objects need destruction between `addNumber` and the catch block

```cpp
catch (std::exception& e) {
    std::cout << e.what() << std::endl;
}
```
- `SpanFullException` inherits from `std::exception`, so this catch matches
- The reference `e` points to the thrown object (this is **polymorphism** — `e.what()` calls `SpanFullException::what()`, not `std::exception::what()`)

**Output:** `Cannot add number: Span is full`

---

### Test 3: No Span — Empty (lines 35–48)

```cpp
Span sp(5);  // empty, size=0
```

```cpp
std::cout << sp.shortestSpan() << std::endl;
```
Inside `shortestSpan()`: `_numbers.size()` is 0 < 2 → `throw NoSpanException()`

**Output:** `shortestSpan: Cannot find span: not enough numbers stored`

```cpp
std::cout << sp.longestSpan() << std::endl;
```
Same thing: size 0 < 2 → throws

**Output:** `longestSpan: Cannot find span: not enough numbers stored`

---

### Test 4: No Span — One Element (lines 50–64)

```cpp
Span sp(5);
sp.addNumber(42);  // vector: [42], size=1
```

Both `shortestSpan()` and `longestSpan()` check `size() < 2` → 1 < 2 is true → both throw.

**Output:**
```
shortestSpan: Cannot find span: not enough numbers stored
longestSpan: Cannot find span: not enough numbers stored
```

You need **at least 2 numbers** to have a "span" (difference) between them.

---

### Test 5: 10,000 Numbers (lines 66–76)

```cpp
Span sp(10000);
```
`_maxSize = 10000`, empty vector.

```cpp
std::srand(42);
```
Seeds the random number generator with 42. `std::srand` sets the **seed** for `std::rand()`. Using the same seed always produces the **same sequence** of pseudo-random numbers — this makes the test **deterministic** and reproducible.

```cpp
for (int i = 0; i < 10000; ++i)
    sp.addNumber(std::rand());
```
Adds 10,000 pseudo-random integers (range 0 to `RAND_MAX`, typically 2,147,483,647). The vector will undergo multiple reallocations as it grows: capacity goes 1→2→4→8→16→...→16384 (enough to hold 10,000).

```cpp
std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
```
- Copies 10,000 elements into `sorted`
- `std::sort` sorts them in O(n log n) ≈ 10000 × ~13.3 ≈ 133,000 comparisons
- Walks through finding minimum adjacent difference

```cpp
std::cout << "Longest span:  " << sp.longestSpan() << std::endl;
```
- `min_element` and `max_element` each do a single O(n) pass

**Output:** (values depend on `std::rand()` implementation, but are deterministic for the same platform)
```
Shortest span: <some small number>
Longest span:  <close to RAND_MAX>
```

---

### Test 6: addRange with Vector Iterators (lines 78–91)

```cpp
Span sp(5);
std::vector<int> v;
v.push_back(100);
v.push_back(200);
v.push_back(300);
v.push_back(400);
v.push_back(500);
```
`v = [100, 200, 300, 400, 500]`

```cpp
sp.addRange(v.begin(), v.end());
```

The compiler **instantiates** the template with `InputIterator = std::vector<int>::iterator`. Execution:

```
Iteration 1: begin points to v[0]=100, *begin = 100, addNumber(100) → _numbers: [100], ++begin
Iteration 2: begin points to v[1]=200, *begin = 200, addNumber(200) → _numbers: [100,200], ++begin
Iteration 3: begin points to v[2]=300, *begin = 300, addNumber(300) → _numbers: [100,200,300], ++begin
Iteration 4: begin points to v[3]=400, *begin = 400, addNumber(400) → _numbers: [100,200,300,400], ++begin
Iteration 5: begin points to v[4]=500, *begin = 500, addNumber(500) → _numbers: [100,200,300,400,500], ++begin
Iteration 6: begin == end → loop exits
```

- `shortestSpan()`: sorted = [100,200,300,400,500], all adjacent diffs = 100 → returns **100**
- `longestSpan()`: max - min = 500 - 100 = **400**

**Output:**
```
Shortest span: 100
Longest span:  400
```

---

### Test 7: addRange with List Iterators (lines 93–105)

```cpp
Span sp(4);
std::list<int> lst;
lst.push_back(5);
lst.push_back(3);
lst.push_back(17);
lst.push_back(9);
```

The list is stored as:
```
[5] ⟷ [3] ⟷ [17] ⟷ [9]
```

```cpp
sp.addRange(lst.begin(), lst.end());
```

The compiler now **instantiates a second version** of `addRange` with `InputIterator = std::list<int>::iterator`. The logic is identical — the only difference is that `++begin` now follows the `next` pointer in the linked list node instead of doing pointer arithmetic.

- `shortestSpan()`: sorted = [3,5,9,17], diffs = [2,4,8] → returns **2**
- `longestSpan()`: 17 - 3 = **14**

**Output:**
```
Shortest span: 2
Longest span:  14
```

---

### Test 8: addRange Overflow (lines 107–124)

```cpp
Span sp(3);
std::vector<int> v;  // v = [1, 2, 3, 4, 5]
```

```cpp
sp.addRange(v.begin(), v.end());
```

Inside `addRange`:
```
Iteration 1: addNumber(1) → size 0 < 3, OK.  _numbers: [1]
Iteration 2: addNumber(2) → size 1 < 3, OK.  _numbers: [1, 2]
Iteration 3: addNumber(3) → size 2 < 3, OK.  _numbers: [1, 2, 3]
Iteration 4: addNumber(4) → size 3 >= 3, THROW SpanFullException!
```

The exception propagates out of `addRange`, out of the try block, caught by `catch`.

**Output:** `Cannot add number: Span is full`

**Key point**: The 3 numbers that were added **before** the exception are **still in the vector**. The exception doesn't roll back previous insertions. So:

```cpp
std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
std::cout << "Longest span:  " << sp.longestSpan() << std::endl;
```
- `_numbers = [1, 2, 3]`
- `shortestSpan()`: sorted = [1,2,3], diffs = [1,1] → returns **1**
- `longestSpan()`: 3 - 1 = **2**

**Output:**
```
Shortest span: 1
Longest span:  2
```

---

### Program Exit (line 126)

```cpp
return 0;
```
All local variables in `main()` have already been destroyed by their scope-closing `}` braces. The program returns 0 (success) to the OS.

---

## Part 3: Complete Expected Output

```
=== Subject test ===
2
14

=== Test: Span full exception ===
Cannot add number: Span is full

=== Test: No span (empty) ===
shortestSpan: Cannot find span: not enough numbers stored
longestSpan: Cannot find span: not enough numbers stored

=== Test: No span (one element) ===
shortestSpan: Cannot find span: not enough numbers stored
longestSpan: Cannot find span: not enough numbers stored

=== Test: 10,000 numbers ===
Shortest span: <platform-dependent>
Longest span:  <platform-dependent>

=== Test: addRange with vector iterators ===
Shortest span: 100
Longest span:  400

=== Test: addRange with list iterators ===
Shortest span: 2
Longest span:  14

=== Test: addRange overflow ===
Cannot add number: Span is full
Shortest span: 1
Longest span:  2
```

---

## Part 4: Makefile Breakdown

| Variable | Value | Meaning |
|----------|-------|---------|
| `CXX` | `c++` | The compiler (typically aliases to g++ or clang++) |
| `CXXFLAGS` | `-Wall -Wextra -Werror -std=c++98` | All warnings on, warnings are errors, C++98 standard |
| `NAME` | `span` | Output binary name |
| `SRCS` | `main.cpp Span.cpp` | Source files to compile |

The `%.o: %.cpp` pattern rule compiles each `.cpp` into a `.o` object file. The `$(NAME)` rule links them into the final executable. The `@` prefix silences the command echo.
