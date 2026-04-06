# CPP Module 08 — Exercise 02: MutantStack — Full Review

---

## 1. Exercise Overview (from the PDF)

| Field | Requirement |
|---|---|
| **Directory** | `ex02/` |
| **Files to submit** | `Makefile`, `main.cpp`, `MutantStack.{h, hpp}` and optional `MutantStack.tpp` |
| **Forbidden** | None |
| **Standard** | C++98 |

### What the PDF asks for

> The `std::stack` container is NOT iterable. Write a `MutantStack` class implemented in terms of `std::stack`. It will offer **all its member functions**, plus an additional feature: **iterators**.

> If you run it with your `MutantStack`, and a second time replacing it with `std::list`, the two outputs should be **the same**.

### Expected output from subject test
```
17
1
5
3
5
737
0
```

Your output with MutantStack: ✅ **matches**
Your output with std::list: ✅ **matches**

---

## 2. Code Review Verdict

> [!NOTE]
> **Overall: ✅ Your code is correct and complete.** No issues found. Everything works.

### ✅ What's good

| Aspect | Why |
|---|---|
| Inherits from `std::stack<T>` | Automatically gets `push()`, `pop()`, `top()`, `size()`, `empty()` for free |
| `this->c` to access underlying container | Correct way to reach the protected member |
| All 4 iterator types provided | `iterator`, `const_iterator`, `reverse_iterator`, `const_reverse_iterator` |
| `typedef` for iterator types | Clean, reusable type aliases |
| OCF implemented | Default, copy, assignment, destructor — all present |
| Copy constructor calls `std::stack<T>(other)` | Delegates to parent — proper chain |
| Assignment calls `std::stack<T>::operator=(other)` | Delegates to parent — proper chain |
| `.tpp` separation | Template declaration in `.hpp`, implementation in `.tpp` |
| `std::list` comparison test | Required by the PDF — outputs match |
| Extra tests | Reverse iterators, empty stack, strings |
| `std::stack<int> s(mstack)` | Required by the subject — proves MutantStack is compatible with std::stack |

---

## 3. New Concepts (not covered in ex00/ex01)

### 3.1 `std::stack` — A container adaptor, not a real container

`std::stack` is **not** a container. It's a **container adaptor** — a wrapper that restricts what you can do with another container.

```
std::stack<int> is actually:
┌──────────────────────────┐
│  std::stack<int>         │  ← adaptor (public interface)
│  ┌────────────────────┐  │
│  │  std::deque<int> c  │  │  ← underlying container (protected member)
│  │  [ 5 | 3 | 5 | 737 ]│  │
│  └────────────────────┘  │
│                          │
│  Exposed:   push() pop() │
│             top() size() │
│             empty()      │
│  Hidden:    begin() end()│  ← NO iterators exposed!
│             insert() []  │
└──────────────────────────┘
```

**Key facts:**
- By default, `std::stack<T>` uses `std::deque<T>` as its underlying container
- The underlying container is stored in a **protected** member called `c`
- `std::stack` deliberately hides iteration — it only exposes LIFO operations (Last In, First Out)
- Being `protected` (not `private`) means **child classes can access `c`** — that's the whole trick

### 3.2 The protected member `c` — How `std::stack` is defined

The C++98 standard defines `std::stack` roughly like this:

```cpp
template <class T, class Container = std::deque<T> >
class stack {
protected:
    Container c;        // ← THIS is what you access with this->c

public:
    void push(const T& x) { c.push_back(x); }
    void pop()             { c.pop_back(); }
    T& top()               { return c.back(); }
    size_type size() const { return c.size(); }
    bool empty() const     { return c.empty(); }
};
```

Every `std::stack` method is just a thin wrapper around the underlying container `c`. The container has `begin()`, `end()`, and full iterator support — `std::stack` just **doesn't expose them**.

Your `MutantStack` inherits from `std::stack` and exposes `c`'s iterators:

```cpp
iterator begin() { return this->c.begin(); }
```

### 3.3 Inheriting from a template class

```cpp
template <typename T>
class MutantStack : public std::stack<T> {
```

This is **class template inheritance** — your template class inherits from another template class.

**What `public` inheritance gives you:**
- All of `std::stack<T>`'s public members (`push`, `pop`, `top`, `size`, `empty`) are automatically available on `MutantStack<T>`
- All of `std::stack<T>`'s protected members (the container `c`) are accessible inside `MutantStack`

**Why `this->c` instead of just `c`?** In a template class that inherits from another template class, the compiler doesn't look into the parent class for names by default. `this->` forces it to look. Without `this->`, the compiler would say `c` is not declared:

```cpp
// Won't compile:
iterator begin() { return c.begin(); }

// Compiles:
iterator begin() { return this->c.begin(); }
```

This is a C++ template rule — **names in dependent base classes require `this->`**.

### 3.4 `typedef` for dependent nested types

```cpp
typedef typename std::stack<T>::container_type::iterator              iterator;
typedef typename std::stack<T>::container_type::const_iterator        const_iterator;
typedef typename std::stack<T>::container_type::reverse_iterator      reverse_iterator;
typedef typename std::stack<T>::container_type::const_reverse_iterator const_reverse_iterator;
```

Let's break down one of these:

```
std::stack<T>::container_type::iterator
│              │               │
│              │               └── the iterator type of the underlying container
│              └── typedef for the container type (std::deque<T> by default)
└── reach into the stack class
```

**Step by step:**
1. `std::stack<T>` — the parent class
2. `::container_type` — a public typedef inside `std::stack` that tells you what container it uses (default: `std::deque<T>`)
3. `::iterator` — the iterator type of that container
4. `typename` — required because the whole thing is a dependent type (depends on `T`)
5. `typedef ... iterator` — creates a type alias so you can write `MutantStack<int>::iterator` instead of the full chain

**The four iterator types:**

| Type | Purpose |
|---|---|
| `iterator` | Read/write, forward traversal (`begin()` → `end()`) |
| `const_iterator` | Read-only, forward traversal |
| `reverse_iterator` | Read/write, backward traversal (`rbegin()` → `rend()`) |
| `const_reverse_iterator` | Read-only, backward traversal |

### 3.5 Reverse iterators — `rbegin()` / `rend()`

```
Container:  [ 5 | 3 | 5 | 737 | 0 ]

Forward:   begin() →→→→→→→→→→→→→→→ end()
            5    3    5   737   0

Reverse:   rend() ←←←←←←←←←←←←←← rbegin()
            5    3    5   737   0
```

- `rbegin()` points to the **last** element
- `rend()` points **before** the first element
- `++rit` moves **backward** (from right to left)

So when you iterate with reverse iterators:
```cpp
for (reverse_iterator rit = rbegin(); rit != rend(); ++rit)
    std::cout << *rit;
// Prints: 0 737 5 3 5  (reversed order)
```

Your test output confirms: `Forward: 1 2 3 4 5` → `Reverse: 5 4 3 2 1` ✅

### 3.6 `const` overloads of `begin()`/`end()`

```cpp
iterator       begin();           // called on non-const MutantStack
const_iterator begin() const;     // called on const MutantStack
```

When you have a `const MutantStack<int>&`, the compiler picks the `const` version, which returns a `const_iterator` — you can read elements but not modify them. This protects const-correctness.

---

## 4. Line-by-Line Breakdown

### [MutantStack.hpp](file:///home/ael-mans/Desktop/CPP-Module/CPP_08/ex02/MutantStack.hpp)

```cpp
template <typename T>
class MutantStack : public std::stack<T> {
```
- Template class `MutantStack<T>` inherits publicly from `std::stack<T>`
- This gives MutantStack all of stack's methods for free

```cpp
public:
    MutantStack();
    MutantStack(const MutantStack& other);
    MutantStack& operator=(const MutantStack& other);
    ~MutantStack();
```
- Orthodox Canonical Form declarations

```cpp
    typedef typename std::stack<T>::container_type::iterator             iterator;
    typedef typename std::stack<T>::container_type::const_iterator       const_iterator;
    typedef typename std::stack<T>::container_type::reverse_iterator     reverse_iterator;
    typedef typename std::stack<T>::container_type::const_reverse_iterator const_reverse_iterator;
```
- Type aliases so users can write `MutantStack<int>::iterator` etc.

```cpp
    iterator               begin();
    iterator               end();
    const_iterator         begin() const;
    const_iterator         end() const;
    reverse_iterator       rbegin();
    reverse_iterator       rend();
    const_reverse_iterator rbegin() const;
    const_reverse_iterator rend() const;
```
- 8 iterator access methods — 4 directions × 2 constness variants

---

### [MutantStack.tpp](file:///home/ael-mans/Desktop/CPP-Module/CPP_08/ex02/MutantStack.tpp)

#### OCF

```cpp
template <typename T>
MutantStack<T>::MutantStack() : std::stack<T>() {}
```
- Default constructor — calls parent's default constructor which creates an empty `deque`

```cpp
template <typename T>
MutantStack<T>::MutantStack(const MutantStack& other) : std::stack<T>(other) {}
```
- Copy constructor — delegates to `std::stack<T>(other)` which copies the underlying `deque`

```cpp
template <typename T>
MutantStack<T>& MutantStack<T>::operator=(const MutantStack& other) {
    if (this != &other)
        std::stack<T>::operator=(other);
    return *this;
}
```
- Assignment — calls parent's `operator=` which copies the `deque`. Self-assignment check.

#### Iterator methods (all follow the same pattern)

```cpp
template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::begin() {
    return this->c.begin();
}
```
- `this->c` — access the protected `deque` inside `std::stack`
- `.begin()` — call the `deque`'s own `begin()` which returns a proper iterator
- Return type is `typename MutantStack<T>::iterator` — the typedef we defined

All 8 methods are identical in structure — they just forward to `this->c.begin()`, `this->c.end()`, `this->c.rbegin()`, or `this->c.rend()`.

---

### [main.cpp](file:///home/ael-mans/Desktop/CPP-Module/CPP_08/ex02/main.cpp) — Test summary

| Test | What it checks | Result |
|---|---|---|
| Subject test | `push`, `pop`, `top`, `size`, iteration, copy to `std::stack` | ✅ output: `17 1 5 3 5 737 0` |
| std::list comparison | Same operations with `std::list` | ✅ output matches MutantStack |
| Reverse iterators | `rbegin()`→`rend()` prints backward | ✅ `5 4 3 2 1` |
| Empty stack | `begin() == end()` on empty stack | ✅ confirmed |
| Strings | `MutantStack<std::string>` | ✅ template works with non-int types |

---

## 5. Summary

Your implementation is **correct and complete** — no issues found.

- ✅ Subject test output matches
- ✅ MutantStack and `std::list` outputs are identical (required by PDF)
- ✅ `std::stack<int> s(mstack)` compiles (proves compatibility)
- ✅ All 4 iterator types work
- ✅ Orthodox Canonical Form
- ✅ Extra tests (reverse, empty, strings)
