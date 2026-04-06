# CPP Module 08 — Exercise 00: Easy Find — Full Review

---

## 1. Exercise Overview (from the PDF)

| Field | Requirement |
|---|---|
| **Directory** | `ex00/` |
| **Files to submit** | `Makefile`, `main.cpp`, `easyfind.{h, hpp}` and optional `easyfind.tpp` |
| **Forbidden** | None |
| **Standard** | C++98 (`-std=c++98 -Wall -Wextra -Werror`) |

### What the PDF asks for

> Write a **function template** `easyfind` that accepts a type `T`. It takes two parameters: the first one is of type `T`, and the second one is an integer.
>
> Assuming `T` is a container of integers, this function has to find the **first occurrence** of the second parameter in the first parameter.
>
> If no occurrence is found, you can either **throw an exception** or **return an error value** of your choice. If you need some inspiration, analyze how standard containers behave.

### Module-specific rules (important)

- You **must** use the STL — containers (`vector`, `list`, `map`, etc.) and algorithms (`<algorithm>`) — wherever appropriate.
- Template implementations can live in `.tpp` files (optional but encouraged).
- Orthodox Canonical Form is required for **classes** (but `easyfind` is a free function template, so OCF doesn't apply here directly).

---

## 2. Code Review Verdict

> [!NOTE]
> **Overall: ✅ Your code is correct and well-structured.** It compiles cleanly under `-std=c++98 -Wall -Wextra -Werror`, handles all edge cases, and follows the 42 guidelines. Below are minor observations — nothing is broken.

### ✅ What's good

| Aspect | Why it's good |
|---|---|
| Uses `std::find` from `<algorithm>` | Exactly what the module expects — use the STL |
| Custom exception class | Clean, inherits from `std::exception`, proper `what()` override |
| Returns an iterator | Lets the caller do more with the result (dereference, erase, etc.) |
| `.tpp` separation | Template declaration in `.hpp`, implementation in `.tpp` — clean pattern |
| Include guards in both files | Prevents double inclusion |
| Tests cover multiple containers | `vector`, `list`, `deque` — proves the template is truly generic |
| Edge cases tested | Empty container, duplicate values, negative numbers, not-found |
| Makefile is correct | Proper flags, clean/fclean/re rules, C++98 standard |

### ⚠️ Minor suggestion

#### Missing `.PHONY` in Makefile

```makefile
# Add this at the end of your Makefile:
.PHONY: all clean fclean re
```

This tells `make` that `all`, `clean`, `fclean`, and `re` are not filenames. Without it, if a file named `clean` existed in the directory, `make clean` would do nothing. Not a big deal in practice, but it's good Makefile hygiene.

---

## 3. Core New Concepts Explained

### 3.1 Function Templates

A **function template** is a blueprint that lets you write one function that works with many types. The compiler generates the actual function code for each type you use.

```cpp
template <typename T>
typename T::iterator easyfind(T& container, int n);
```

**How it works step by step:**

1. **`template <typename T>`** — This tells the compiler: "The following function is a template. `T` is a placeholder for any type. Don't generate code yet — wait until someone calls it with a specific type."

2. **`typename T::iterator`** — This is the **return type**. It says: "Whatever type `T` is, reach inside it and find its nested type called `iterator`." The `typename` keyword is required here because `T::iterator` is a **dependent type** — the compiler doesn't know what `T` is yet, so it can't tell if `T::iterator` is a type or a value. `typename` disambiguates: "Trust me, this is a type."

3. **`T& container`** — The container is passed by **reference** (not by value). This avoids copying the entire container, which would be expensive.

4. **When you call `easyfind(v, 30)`** where `v` is a `std::vector<int>`:
   - The compiler deduces `T = std::vector<int>`
   - It generates a concrete function: `std::vector<int>::iterator easyfind(std::vector<int>& container, int n)`
   - This process is called **template instantiation**

5. **Why the `.tpp` file?** — Template code must be visible at the point of use (because the compiler generates code per type). You can't put it in a `.cpp` file like normal functions. The `.tpp` pattern keeps the declaration in the `.hpp` and the implementation in a separate file, but the `#include "easyfind.tpp"` at the bottom of the `.hpp` makes it all visible together.

---

### 3.2 STL Containers

The **Standard Template Library (STL)** provides generic container classes. Your code uses three:

#### `std::vector<int>`
```
Memory layout:  [ 10 | 20 | 30 | 40 | 50 ]
Index:             0    1    2    3    4
```
- **Contiguous memory** — elements are stored side by side like a C array
- **Random access** — `v[2]` is O(1), you can jump to any element instantly
- **Dynamic size** — grows automatically when you `push_back()`
- **Iterator type** — **Random-access iterator** (supports `+`, `-`, `<`, `[]`)

#### `std::list<int>`
```
Memory layout:  [1] <-> [2] <-> [3] <-> [4] <-> [5]
                 ↑                                ↑
               begin()                          end()-1
```
- **Doubly-linked list** — each element is a node with pointers to prev/next
- **No random access** — you can't do `lst[2]`, you must walk from the beginning
- **Fast insert/delete** — O(1) if you have an iterator to the position
- **Iterator type** — **Bidirectional iterator** (supports `++`, `--` but NOT `+`, `-`)

#### `std::deque<int>`
```
Memory layout:  [ block1 ][ block2 ][ block3 ]
                  -1, 0       1
```
- **Double-ended queue** — efficient insert/remove at both front and back
- **Random access** — `dq[1]` works in O(1), like vector
- **Segmented memory** — stored in chunks (not fully contiguous like vector)
- **Iterator type** — **Random-access iterator**

---

### 3.3 Iterators

An **iterator** is an object that acts like a pointer to an element in a container. It provides a uniform way to traverse any container without knowing its internal structure.

```
Container:  [ 10 | 20 | 30 | 40 | 50 ]
              ↑                         ↑
           begin()                    end()    ← end() points PAST the last element
```

**Key operations:**

| Operation | Meaning | Example |
|---|---|---|
| `container.begin()` | Iterator to the **first** element | `it = v.begin()` → points to 10 |
| `container.end()` | Iterator **past** the last element | Never dereference `end()` |
| `*it` | **Dereference** — get the value the iterator points to | `*it` → `10` |
| `++it` | Move to the **next** element | After `++it`, points to 20 |
| `--it` | Move to the **previous** element (bidirectional+) | |
| `it == container.end()` | Check if we've gone past all elements | Used to detect "not found" |

**Why `end()` points past the last element?** This is the "half-open range" convention `[begin, end)`. It makes loops clean:
```cpp
for (it = v.begin(); it != v.end(); ++it)
    std::cout << *it;
```
When the container is **empty**, `begin() == end()`, so the loop body never executes — no special case needed.

---

### 3.4 `std::find` Algorithm

```cpp
#include <algorithm>

template <class InputIterator, class T>
InputIterator find(InputIterator first, InputIterator last, const T& value);
```

`std::find` is a **generic algorithm** that searches for a value in a range `[first, last)`.

**How it works internally** (simplified):
```cpp
template <class InputIterator, class T>
InputIterator find(InputIterator first, InputIterator last, const T& value) {
    while (first != last) {     // Walk through each element
        if (*first == value)    // Dereference and compare
            return first;       // Found it! Return iterator to this element
        ++first;                // Move to next element
    }
    return last;                // Reached the end — not found
}
```

**Key behaviors:**
- Returns an iterator to the **first** matching element
- If not found, returns `last` (which is `container.end()`)
- Uses `operator==` to compare elements
- Works with **any** container that provides iterators
- Time complexity: **O(n)** — linear scan

---

## 4. Line-by-Line Breakdown

### [easyfind.hpp](file:///home/ael-mans/Desktop/CPP-Module/CPP_08/ex00/easyfind.hpp)

```cpp
#ifndef EASYFIND_HPP          // Include guard — prevents double inclusion
#define EASYFIND_HPP

#include <algorithm>           // For std::find
#include <exception>           // For std::exception base class

class NotFoundException : public std::exception {
```
- Defines a **custom exception class**
- Inherits from `std::exception` — this lets it be caught by `catch (std::exception& e)`
- `public` inheritance means `NotFoundException` "is-a" `std::exception`

```cpp
public:
    const char* what() const throw() {
        return "Element not found in container";
    }
```
- **`what()`** — virtual function from `std::exception` that returns an error message
- **`const`** after `what()` — this is a `const` member function, it promises not to modify the object
- **`throw()`** — C++98 exception specification meaning "this function will never throw"
- Returns a `const char*` (string literal) — string literals have static storage, so the pointer remains valid

```cpp
};

template <typename T>
typename T::iterator easyfind(T& container, int n);
```
- **Template declaration** — tells the compiler this function exists but the body is elsewhere
- `typename T::iterator` — return type is whatever iterator type `T` defines

```cpp
#include "easyfind.tpp"        // Pull in the implementation
#endif
```
- Includes the `.tpp` file so the compiler sees the full template definition

---

### [easyfind.tpp](file:///home/ael-mans/Desktop/CPP-Module/CPP_08/ex00/easyfind.tpp)

```cpp
#ifndef EASYFIND_TPP
#define EASYFIND_TPP

template <typename T>
typename T::iterator easyfind(T& container, int n) {
```
- Full function template definition
- `T` will be deduced by the compiler from the argument type

```cpp
    typename T::iterator it = std::find(container.begin(), container.end(), n);
```

**This single line does a lot:**

1. `container.begin()` — get an iterator to the first element
2. `container.end()` — get an iterator past the last element
3. `std::find(begin, end, n)` — search for value `n` in the range `[begin, end)`
4. `typename T::iterator it` — store the result. If found, `it` points to the matching element. If not found, `it == container.end()`

The `typename` keyword is needed because `T::iterator` is a **dependent name** — the compiler can't resolve it until `T` is known.

```cpp
    if (it == container.end())
        throw NotFoundException();
    return it;
```
- If `std::find` returned `end()`, the element was not found → throw our custom exception
- Otherwise, return the iterator pointing to the found element

---

### [main.cpp](file:///home/ael-mans/Desktop/CPP-Module/CPP_08/ex00/main.cpp) — Test by test

#### Test 1: Vector — found and not-found (lines 8–30)
```cpp
std::vector<int> v;
v.push_back(10); v.push_back(20); v.push_back(30); ...
```
- Creates a vector `[10, 20, 30, 40, 50]`
- `easyfind(v, 30)` → **found**, `std::find` returns iterator to `30`, prints "Found: 30"
- `easyfind(v, 42)` → **not found**, `std::find` returns `v.end()`, exception thrown, prints "Element not found in container"

#### Test 2: List — found, found, not-found (lines 32–61)
```cpp
std::list<int> lst;
lst.push_back(1); ... lst.push_back(5);
```
- Creates a list `{1, 2, 3, 4, 5}`
- `easyfind(lst, 1)` → found (first element)
- `easyfind(lst, 5)` → found (last element)
- `easyfind(lst, 99)` → not found → exception

This proves the template works with `std::list` (bidirectional iterators), not just `std::vector`.

#### Test 3: Deque — negative numbers (lines 63–83)
```cpp
std::deque<int> dq;
dq.push_back(-1); dq.push_back(0); dq.push_back(1);
```
- Tests with negative values and zero
- `easyfind(dq, 0)` → found, `easyfind(dq, -1)` → found
- Proves the template works with `std::deque` too

#### Test 4: Empty container (lines 85–95)
```cpp
std::vector<int> empty;
easyfind(empty, 1);  // → exception
```
- On an empty container, `begin() == end()`, so `std::find` immediately returns `end()`
- Exception thrown — this is the correct behavior

#### Test 5: Duplicate values (lines 97–111)
```cpp
std::vector<int> v;  // [5, 10, 5, 20]
std::vector<int>::iterator it = easyfind(v, 5);
std::cout << *it << " at index " << (it - v.begin());  // "5 at index 0"
```
- When there are duplicates, `std::find` returns the **first** occurrence (index 0, not index 2)
- `it - v.begin()` calculates the index via pointer arithmetic (only valid for random-access iterators)

---

## 5. Execution Flow Diagram

```mermaid
sequenceDiagram
    participant main
    participant easyfind
    participant std::find
    participant container

    main->>easyfind: easyfind(v, 30)
    easyfind->>container: container.begin()
    container-->>easyfind: iterator to first element
    easyfind->>container: container.end()
    container-->>easyfind: iterator past last element
    easyfind->>std::find: find(begin, end, 30)
    std::find->>std::find: compare *it == 30 for each element
    std::find-->>easyfind: iterator to element 30
    easyfind->>easyfind: it != end() → element found
    easyfind-->>main: returns iterator to 30
    main->>main: *it → prints "Found: 30"
```

```mermaid
sequenceDiagram
    participant main
    participant easyfind
    participant std::find

    main->>easyfind: easyfind(v, 42)
    easyfind->>std::find: find(begin, end, 42)
    std::find->>std::find: scans all elements, none match
    std::find-->>easyfind: returns end()
    easyfind->>easyfind: it == end() → throw NotFoundException
    easyfind-->>main: exception propagates
    main->>main: catch block prints "Element not found in container"
```

---

## 6. Summary

Your implementation is **solid and correct**. The only suggestion is:

1. **Optional**: Add `.PHONY` to the Makefile

Everything else — the template structure, the `.tpp` separation, the exception handling, the test coverage — is exactly what 42 expects for this exercise. ✅
