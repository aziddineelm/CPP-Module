# CPP Module 08 — Exercise 01: Span — Full Review

---

## 1. Exercise Overview (from the PDF)

| Field | Requirement |
|---|---|
| **Directory** | `ex01/` |
| **Files to submit** | `Makefile`, `main.cpp`, `Span.{h, hpp}`, `Span.cpp` |
| **Forbidden** | None |
| **Standard** | C++98 |

### What the PDF asks for

1. A **`Span` class** that stores a maximum of **N integers** (N is `unsigned int`, passed to the constructor)
2. **`addNumber(int)`** — adds one number. Throws an exception if already N elements stored
3. **`shortestSpan()`** — returns the smallest difference between any two stored numbers
4. **`longestSpan()`** — returns the largest difference between any two stored numbers
5. Both span functions throw if there are **0 or 1** elements (can't compute a span)
6. Must test with **at least 10,000 numbers**
7. Must implement a way to **add multiple numbers using a range of iterators** (not just one by one)

### Expected output from subject test
```
2
14
```
Your output: ✅ **matches exactly**

---

## 2. Code Review Verdict

> [!NOTE]
> **Overall: ✅ Your code is correct.** It meets all requirements, compiles cleanly, and handles every edge case. One real issue to address below.

### ✅ What's good

| Aspect | Why |
|---|---|
| Orthodox Canonical Form | Default, parameterized, copy constructor, assignment operator, destructor — all present |
| `addRange()` template function | Fulfills the "range of iterators" requirement from the PDF |
| Nested exception classes | Clean pattern, properly inherits `std::exception` |
| `shortestSpan()` sorts a copy | Doesn't modify the original `_numbers` — correct approach |
| `longestSpan()` uses `min_element`/`max_element` | Uses the STL as the module expects |
| Tests cover 10,000+ numbers | Required by the PDF |
| Tests `addRange` with both `vector` and `list` iterators | Proves the template is generic |
| Tests overflow with `addRange` | Good edge case |

### ✅ Fixed: integer overflow in span calculations

The return types of `shortestSpan()` and `longestSpan()` were changed to `long long`, and `static_cast<long long>` is used before subtraction. This correctly handles `INT_MAX - INT_MIN = 4294967295`.

---

## 3. New Concepts (not covered in ex00)

### 3.1 `std::sort` — Sorting a range

```cpp
#include <algorithm>

std::sort(sorted.begin(), sorted.end());
```

`std::sort` reorders elements in the range `[first, last)` in **ascending order**.

**How it works internally:**
- Uses **Introsort** — a hybrid of quicksort, heapsort, and insertion sort
- Average time: **O(n log n)**
- It modifies the container **in place** (that's why you create a copy first)

**Step by step on your data `{6, 3, 17, 9, 11}`:**
```
Before sort: [ 6, 3, 17, 9, 11 ]
After sort:  [ 3, 6, 9, 11, 17 ]
```

**Why sort for shortestSpan?** The shortest span must be between two **adjacent** elements in sorted order. If `a ≤ b ≤ c`, then `b - a ≤ c - a` and `c - b ≤ c - a`. So you don't need to compare every pair — just adjacent ones after sorting. This reduces the algorithm from O(n²) to O(n log n).

---

### 3.2 `std::min_element` / `std::max_element` — Finding extremes

```cpp
int min = *std::min_element(_numbers.begin(), _numbers.end());
int max = *std::max_element(_numbers.begin(), _numbers.end());
```

These scan the entire range and return an **iterator** to the smallest/largest element.

**How `std::min_element` works internally:**
```cpp
template <class Iterator>
Iterator min_element(Iterator first, Iterator last) {
    Iterator smallest = first;
    while (++first != last) {
        if (*first < *smallest)
            smallest = first;
    }
    return smallest;
}
```

- Time: **O(n)** — single pass
- Returns an **iterator**, so you dereference with `*` to get the value
- For `longestSpan()`, the longest distance is always `max - min`

---

### 3.3 Member function templates inside a class

```cpp
// Declaration in Span.hpp (inside the class):
template <typename InputIterator>
void addRange(InputIterator begin, InputIterator end);

// Definition in Span.hpp (outside the class, but still in the header):
template <typename InputIterator>
void Span::addRange(InputIterator begin, InputIterator end) {
    while (begin != end) {
        addNumber(*begin);
        ++begin;
    }
}
```

This is different from ex00's free function template — this is a **member function template** inside a class.

**Key points:**
- The template definition must be in the **header file** (not `.cpp`) because the compiler needs to see it when instantiating
- `InputIterator` is a generic type — it works with `std::vector<int>::iterator`, `std::list<int>::iterator`, or any iterator type
- It reuses `addNumber()` which handles the overflow check — so `addRange` automatically throws if the span gets full mid-insertion

**When you call `sp.addRange(v.begin(), v.end())`:**
1. Compiler deduces `InputIterator = std::vector<int>::iterator`
2. Generates a concrete function for that type
3. The loop dereferences each iterator (`*begin`) to get the `int` value and passes it to `addNumber()`

---

### 3.4 Nested exception classes

```cpp
class Span {
    // ...
    class SpanFullException : public std::exception {
    public:
        const char* what() const throw();
    };

    class NoSpanException : public std::exception {
    public:
        const char* what() const throw();
    };
};
```

In ex00, the exception was a **standalone class**. Here, the exceptions are **nested inside** the `Span` class.

**What this means:**
- `SpanFullException` and `NoSpanException` exist inside `Span`'s scope
- Outside the class, you refer to them as `Span::SpanFullException`
- When implementing `what()` in the `.cpp`, you use the full scope: `Span::SpanFullException::what()`
- This is cleaner because the exceptions are logically tied to the `Span` class — they don't pollute the global namespace

---

### 3.5 `std::vector` copy constructor for sorting

```cpp
std::vector<int> sorted(_numbers);
```

This creates a **copy** of `_numbers`. The `std::vector` copy constructor:
1. Allocates new memory for `sorted`
2. Copies every element from `_numbers` into `sorted`
3. `sorted` is now an independent copy — modifying it doesn't affect `_numbers`

This is important because `std::sort` modifies the container in place, and `shortestSpan()` is a `const` method — it cannot modify `_numbers`. So you sort the copy instead.

---

### 3.6 `size_type` — the proper type for container sizes

```cpp
for (std::vector<int>::size_type i = 2; i < sorted.size(); ++i)
```

`std::vector<int>::size_type` is a typedef for `unsigned` integer type (typically `size_t`). It matches the return type of `.size()`.

Why use it instead of `int`? Comparing a signed `int` with an unsigned `size()` would produce a compiler warning with `-Wextra`. Using `size_type` avoids that warning.

---

## 4. Line-by-Line Breakdown

### [Span.hpp](file:///home/ael-mans/Desktop/CPP-Module/CPP_08/ex01/Span.hpp)

```cpp
class Span {
private:
    unsigned int        _maxSize;      // Maximum number of elements allowed
    std::vector<int>    _numbers;      // Internal storage for the integers
```
- `_maxSize` is the capacity limit set at construction
- `_numbers` is the actual container — starts empty, grows with `push_back`
- Using `std::vector` is the right choice: dynamic array, random access, works with `std::sort`

```cpp
public:
    Span();                           // Default constructor
    Span(unsigned int n);             // Parameterized constructor — sets _maxSize
    Span(const Span& other);          // Copy constructor
    Span& operator=(const Span& other); // Copy assignment
    ~Span();                          // Destructor
```
- Full **Orthodox Canonical Form** — required by the subject for all classes

---

### [Span.cpp](file:///home/ael-mans/Desktop/CPP-Module/CPP_08/ex01/Span.cpp)

#### Constructors and OCF

```cpp
Span::Span() : _maxSize(0) {}
```
- Default constructor: `_maxSize = 0`, `_numbers` is default-constructed (empty vector)
- A Span with `_maxSize = 0` can't store any numbers

```cpp
Span::Span(unsigned int n) : _maxSize(n) {}
```
- Sets the capacity. `_numbers` vector is created empty — it will grow as you add numbers

```cpp
Span::Span(const Span& other) : _maxSize(other._maxSize), _numbers(other._numbers) {}
```
- **Initializer list** copies both fields. `_numbers(other._numbers)` invokes vector's copy constructor — deep copy of all elements

```cpp
Span& Span::operator=(const Span& other) {
    if (this != &other) {                    // Self-assignment check
        _maxSize = other._maxSize;
        _numbers = other._numbers;           // Vector's operator= does deep copy
    }
    return *this;
}
```
- `this != &other` prevents self-assignment (`sp = sp`)
- Returns `*this` to allow chaining: `a = b = c`

#### `addNumber`

```cpp
void Span::addNumber(int number) {
    if (_numbers.size() >= _maxSize)
        throw SpanFullException();
    _numbers.push_back(number);
}
```
1. Check if we've reached the limit — `.size()` returns how many elements are currently stored
2. If full, throw
3. Otherwise, `push_back` adds the element at the end of the vector

#### `shortestSpan`

```cpp
int Span::shortestSpan() const {
    if (_numbers.size() < 2)
        throw NoSpanException();

    std::vector<int> sorted(_numbers);           // Copy the vector
    std::sort(sorted.begin(), sorted.end());     // Sort the copy ascending

    int minSpan = sorted[1] - sorted[0];         // Start with first pair
    for (std::vector<int>::size_type i = 2; i < sorted.size(); ++i) {
        int diff = sorted[i] - sorted[i - 1];   // Difference between adjacent
        if (diff < minSpan)
            minSpan = diff;                      // Keep track of smallest
    }
    return minSpan;
}
```

**Walkthrough with `{6, 3, 17, 9, 11}`:**
```
sorted = {3, 6, 9, 11, 17}

i=0→1:  6 - 3  = 3   → minSpan = 3
i=1→2:  9 - 6  = 3   → minSpan = 3 (tie)
i=2→3:  11 - 9 = 2   → minSpan = 2 ← new minimum
i=3→4:  17 - 11 = 6  → minSpan still 2

return 2 ✅
```

#### `longestSpan`

```cpp
int Span::longestSpan() const {
    if (_numbers.size() < 2)
        throw NoSpanException();

    int min = *std::min_element(_numbers.begin(), _numbers.end());
    int max = *std::max_element(_numbers.begin(), _numbers.end());
    return max - min;
}
```

**Walkthrough with `{6, 3, 17, 9, 11}`:**
```
min_element scans: 6, 3←min, 17, 9, 11 → returns iterator to 3 → *it = 3
max_element scans: 6, 3, 17←max, 9, 11 → returns iterator to 17 → *it = 17

return 17 - 3 = 14 ✅
```

---

### [main.cpp](file:///home/ael-mans/Desktop/CPP-Module/CPP_08/ex01/main.cpp) — Test summary

| Test | What it checks | Result |
|---|---|---|
| Subject test | `{6,3,17,9,11}` → shortest=2, longest=14 | ✅ matches PDF |
| Span full | Adding 4th element to Span(3) | ✅ throws `SpanFullException` |
| No span (empty) | `shortestSpan()` on empty Span | ✅ throws `NoSpanException` |
| No span (one element) | `shortestSpan()` with 1 element | ✅ throws `NoSpanException` |
| 10,000 numbers | Random fill + compute spans | ✅ works, required by PDF |
| addRange (vector) | `{100,200,300,400,500}` → shortest=100, longest=400 | ✅ |
| addRange (list) | `{5,3,17,9}` → same as subject minus one element | ✅ |
| addRange overflow | 5 elements into Span(3) | ✅ throws after 3, still computes spans for the 3 that got in |

---

## 5. Summary

Your implementation is **correct and complete**. It meets every requirement from the PDF:
- ✅ `addNumber()` with overflow exception
- ✅ `shortestSpan()` and `longestSpan()` with proper exception for < 2 elements
- ✅ Range insertion via `addRange()` with iterator template
- ✅ 10,000 number test
- ✅ Orthodox Canonical Form
- ✅ Subject test output matches (`2` and `14`)

The only real issue is the potential **integer overflow** in span calculations with extreme values — see section 2 for the fix if you want to handle it.
