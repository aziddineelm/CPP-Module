# CPP_08/ex02 — MutantStack: Complete Explanation

> This document covers **only new concepts** not already explained in the ex00/ex01 walkthroughs. Templates, iterators basics, vector, list, the `.tpp` pattern, and custom exceptions were covered there.

---

## Part 1: New Concepts

### 1. `std::stack` — A Container **Adapter** (Not a Container)

This is the **most important concept** to understand. `std::stack` is **not** a container like `std::vector` or `std::list`. It's a **container adapter** — a wrapper that takes an existing container and restricts its interface.

```cpp
// Simplified std::stack implementation (what the STL actually looks like):
template <typename T, typename Container = std::deque<T> >
class stack {
protected:
    Container c;    // ← THE underlying container. THIS is where the data lives.

public:
    void push(const T& x)  { c.push_back(x); }
    void pop()              { c.pop_back(); }
    T& top()                { return c.back(); }
    bool empty() const      { return c.empty(); }
    size_t size() const     { return c.size(); }
};
```

Key insights:

1. **`std::stack` doesn't store data itself.** It has a member `c` of type `Container` (defaults to `std::deque<T>`) that stores everything.
2. **It restricts the interface.** A deque supports `push_front`, `push_back`, `operator[]`, iterators, etc. A stack only exposes `push`, `pop`, `top`, `empty`, `size` — enforcing LIFO (Last-In-First-Out) discipline.
3. **`c` is `protected`** — meaning **derived classes** can access it, but outside code cannot.
4. **A stack has NO iterators.** By design, you're only supposed to see the top element. That's the whole point of this exercise — to add them back.

#### Why `std::deque` is the default (not `std::vector`)

`std::deque` never needs to **reallocate and copy** all elements when it grows (it just allocates new blocks). `std::vector` does. For a stack where you're constantly pushing/popping, deque avoids worst-case O(n) reallocations. In practice, the performance difference is small, but deque is technically better suited.

---

### 2. Inheriting from a Template Class

```cpp
template <typename T>
class MutantStack : public std::stack<T> {
```

This is **class template inheritance**. Let's break it down completely:

#### `template <typename T>`
`MutantStack` is itself a template — it works with any type (`int`, `std::string`, etc.).

#### `: public std::stack<T>`
`MutantStack<T>` publicly inherits from `std::stack<T>`. This means:
- **All public members** of `std::stack<T>` become public members of `MutantStack<T>` — so `push()`, `pop()`, `top()`, `size()`, `empty()` are all available automatically, inherited for free
- **All protected members** of `std::stack<T>` become protected members of `MutantStack<T>` — so `MutantStack` can access `this->c` directly

```
Class hierarchy:

  std::stack<int>
  ├── protected: c (a std::deque<int>)
  ├── public: push(), pop(), top(), size(), empty()
  │
  └── MutantStack<int>  (inherits everything above)
      ├── can access this->c ✅ (because it's protected, not private)
      └── public: begin(), end(), rbegin(), rend() (NEW — added by us)
```

#### Why `this->c` and not just `c`?

In a template class inheriting from a template base, the compiler **doesn't automatically look** into the base class for names. This is because the base class depends on `T`, and different specializations of `std::stack<T>` could have completely different members. The compiler can't assume `c` exists until it knows what `T` is.

Writing `this->c` explicitly tells the compiler: "look in this object (and its base classes) for `c`". Without `this->`, you'd get a compilation error: `c was not declared in this scope`.

```cpp
// This would NOT compile:
return c.begin();          // ❌ compiler doesn't search base class

// This compiles:
return this->c.begin();    // ✅ explicitly tells compiler to look in base
```

---

### 3. `container_type` — Accessing the Underlying Container's Type

```cpp
typedef typename std::stack<T>::container_type::iterator   iterator;
```

Let's trace this chain step by step:

```
std::stack<T>::container_type
       ↓
This is a typedef inside std::stack that equals the template parameter Container.
Since we didn't specify one, it defaults to std::deque<T>.
       ↓
std::deque<T>
       ↓
std::deque<T>::iterator
       ↓
This is the iterator type for deque — a random-access iterator.
```

So when `T = int`:
```
std::stack<int>::container_type          = std::deque<int>
std::stack<int>::container_type::iterator = std::deque<int>::iterator
```

The `typedef` creates a **shortcut name** so you can write `MutantStack<int>::iterator` instead of `std::deque<int>::iterator`. This is essential because:
1. Users shouldn't need to know the underlying container is a deque
2. It follows the same naming convention as all STL containers (`container::iterator`)

---

### 4. `typedef` — Creating Type Aliases (C++98 Style)

```cpp
typedef typename std::stack<T>::container_type::iterator   iterator;
```

`typedef` creates a new name for an existing type. The syntax is:
```cpp
typedef existing_type new_name;
```

It reads "backwards" compared to how you'd say it in English. Think of it as declaring a variable, then replacing the variable name with the alias and adding `typedef` in front.

In C++11, this would be written more readably as:
```cpp
using iterator = typename std::stack<T>::container_type::iterator;  // C++11
```

But since this project uses C++98 (`-std=c++98`), `typedef` is required.

The `typename` keyword is needed (as covered in ex00) because everything depends on the template parameter `T`.

---

### 5. Four Iterator Types Exposed

```cpp
typedef ... iterator;                // read-write, forward
typedef ... const_iterator;          // read-only, forward
typedef ... reverse_iterator;        // read-write, backward
typedef ... const_reverse_iterator;  // read-only, backward
```

#### Forward vs Reverse Iterators

```
Container: [5, 3, 5, 737, 0]
             ↑                 ↑
           begin()           end()    (forward: left → right)

             ↑                 ↑
           rend()           rbegin()  (reverse: right → left)
```

- **`begin()`** → points to the **first** element
- **`end()`** → points **one past the last** element
- **`rbegin()`** → points to the **last** element
- **`rend()`** → points **one before the first** element

When you `++rit` on a reverse iterator, it moves **left** (toward the beginning). This is because a reverse iterator wraps a normal iterator and reverses the direction of `++` and `--`:

```cpp
// Simplified reverse_iterator implementation:
template <typename Iterator>
class reverse_iterator {
    Iterator current;  // wraps a normal iterator
public:
    reverse_iterator& operator++() {
        --current;     // ++ on reverse means -- on the underlying iterator
        return *this;
    }
    T& operator*() {
        Iterator tmp = current;
        --tmp;
        return *tmp;   // dereferences one before current
    }
};
```

Why does `*rit` dereference one position before `current`? Because `rbegin()` is constructed from `end()`, which points past the last element. To access the last element, it needs to step back by one.

#### Const vs Non-const Iterators

- **`iterator`**: you can read **and modify** the element: `*it = 42;` ✅
- **`const_iterator`**: you can only **read** the element: `*it = 42;` ❌ compile error

Const iterators are returned when you call `begin()`/`end()` on a **const** object:
```cpp
void printStack(const MutantStack<int>& ms) {
    // ms is const, so ms.begin() returns const_iterator
    MutantStack<int>::const_iterator it = ms.begin();
    // *it = 42;  ← would NOT compile
}
```

---

### 6. The Orthodox Canonical Form — Template Version

```cpp
template <typename T>
MutantStack<T>::MutantStack() : std::stack<T>() {}
```

The constructor explicitly calls the **base class constructor** `std::stack<T>()`. This initializes the protected member `c` (the underlying deque) through `std::stack`'s own constructor.

```cpp
template <typename T>
MutantStack<T>::MutantStack(const MutantStack& other) : std::stack<T>(other) {}
```

The copy constructor passes `other` to `std::stack<T>`'s copy constructor. Since `MutantStack` inherits from `std::stack`, and `other` **is-a** `std::stack`, this works directly. The base copy constructor copies `other.c` — which deep-copies the entire deque.

```cpp
template <typename T>
MutantStack<T>& MutantStack<T>::operator=(const MutantStack& other) {
    if (this != &other)
        std::stack<T>::operator=(other);
    return *this;
}
```

The assignment operator delegates to `std::stack<T>::operator=`, which handles copying `c`. The self-assignment check (`this != &other`) prevents destroying your own data when you write `ms = ms`.

```cpp
template <typename T>
MutantStack<T>::~MutantStack() {}
```

Empty destructor — the base class `std::stack<T>` destructor (which destroys `c`, which destroys the deque, which frees all memory) is called **automatically** after this runs.

---

### 7. Object Slicing — `std::stack<int> s(mstack)`

```cpp
std::stack<int> s(mstack);
```

This constructs a `std::stack<int>` from a `MutantStack<int>`. Since `MutantStack` inherits from `std::stack`, the compiler treats `mstack` as a `std::stack<int>&` and calls `std::stack`'s copy constructor.

**But**: `s` is a plain `std::stack<int>`, **not** a `MutantStack<int>`. The `MutantStack`-specific parts (the iterator methods) are **sliced off**. `s` has no `begin()`, no `end()`, no iterators. Only `push`, `pop`, `top`, `size`, `empty`.

```
mstack (MutantStack<int>):
├── stack part: c = [5, 3, 5, 737, 0]
├── push(), pop(), top(), size(), empty()
└── begin(), end(), rbegin(), rend()  ← MutantStack additions

s (std::stack<int>):
├── stack part: c = [5, 3, 5, 737, 0]  ← copied
└── push(), pop(), top(), size(), empty()
    (NO iterators — sliced off)
```

---

### 8. `std::stack` Member Functions (Inherited by MutantStack)

Since `MutantStack` inherits publicly from `std::stack`, it gets all these for free:

| Function | What it does | Underlying deque call |
|----------|-------------|----------------------|
| `push(x)` | Adds element to the top of the stack | `c.push_back(x)` |
| `pop()` | Removes the top element (returns nothing!) | `c.pop_back()` |
| `top()` | Returns a **reference** to the top element | `c.back()` |
| `size()` | Returns number of elements | `c.size()` |
| `empty()` | Returns true if the stack has no elements | `c.empty()` |

> **Important**: `pop()` does **not** return the removed element. It's `void`. If you want the value, you must call `top()` first, then `pop()`. This is a deliberate C++ design choice for exception safety.

---

## Part 2: Line-by-Line Execution Flow

### Test 1: Subject Test — MutantStack (lines 6–34)

```cpp
MutantStack<int> mstack;
```
1. The compiler instantiates `MutantStack<int>` and its base `std::stack<int>`
2. `std::stack<int>` constructs its protected member `c` — a `std::deque<int>` — empty
3. Stack state: `c = []`, size = 0

```cpp
mstack.push(5);
```
- Inherited from `std::stack` → calls `c.push_back(5)`
- The deque allocates an internal block and stores 5
- Stack state: `c = [5]` (5 is at the top/back)

```cpp
mstack.push(17);
```
- `c.push_back(17)`
- Stack state: `c = [5, 17]` (17 is at the top/back)

```cpp
std::cout << mstack.top() << std::endl;
```
- `top()` → `c.back()` → returns reference to `17`
- **Output:** `17`

```cpp
mstack.pop();
```
- `pop()` → `c.pop_back()` → removes 17 from the deque
- Stack state: `c = [5]`, size = 1

```cpp
std::cout << mstack.size() << std::endl;
```
- `size()` → `c.size()` → returns 1
- **Output:** `1`

```cpp
mstack.push(3);     // c = [5, 3]
mstack.push(5);     // c = [5, 3, 5]
mstack.push(737);   // c = [5, 3, 5, 737]
mstack.push(0);     // c = [5, 3, 5, 737, 0]
```

Now the deque (and hence the stack) contains: `[5, 3, 5, 737, 0]`

```
The deque's memory layout (conceptual):

  Bottom of stack                    Top of stack
  (front of deque)                   (back of deque)
  [ 5 | 3 | 5 | 737 | 0 ]
    ↑                       ↑
  begin()                 end()
```

```cpp
MutantStack<int>::iterator it = mstack.begin();
```
- `begin()` calls `this->c.begin()` → returns a `std::deque<int>::iterator` pointing to the **first element** (bottom of stack) = 5

```cpp
MutantStack<int>::iterator ite = mstack.end();
```
- `end()` calls `this->c.end()` → returns iterator one past the **last element** (past the top of stack)

```cpp
++it;
```
- Iterator now points to the **second element** = 3

```cpp
--it;
```
- Iterator now points back to the **first element** = 5
- These two operations together are a no-op / sanity test proving the iterator supports both directions

```cpp
while (it != ite) {
    std::cout << *it << std::endl;
    ++it;
}
```
Iteration (bottom to top of stack):
```
Iteration 1: *it = 5,   print 5,   ++it → points to 3
Iteration 2: *it = 3,   print 3,   ++it → points to 5
Iteration 3: *it = 5,   print 5,   ++it → points to 737
Iteration 4: *it = 737, print 737, ++it → points to 0
Iteration 5: *it = 0,   print 0,   ++it → points to end()
Iteration 6: it == ite → exit loop
```

**Output:**
```
5
3
5
737
0
```

```cpp
std::stack<int> s(mstack);
```
- **Object slicing**: copies the `std::stack<int>` portion of `mstack` into `s`
- `s` contains `[5, 3, 5, 737, 0]` but has **no iterators**
- No output — this just proves the copy works

The `}` at line 34 destroys `mstack` and `s` — their deques' destructors free all memory.

---

### Test 2: Same Test with `std::list` (lines 36–63)

This test replaces `MutantStack` with `std::list` to prove they produce **identical output**. The equivalences:

| MutantStack | std::list |
|-------------|-----------|
| `push(x)` | `push_back(x)` |
| `top()` | `back()` |
| `pop()` | `pop_back()` |
| `size()` | `size()` |
| `begin()` / `end()` | `begin()` / `end()` |

```cpp
std::list<int> mstack;
mstack.push_back(5);
mstack.push_back(17);
std::cout << mstack.back() << std::endl;    // 17
mstack.pop_back();                           // removes 17
std::cout << mstack.size() << std::endl;     // 1
mstack.push_back(3);
mstack.push_back(5);
mstack.push_back(737);
mstack.push_back(0);
// list: [5, 3, 5, 737, 0] — same contents
```

The iteration loop produces the same output: `5 3 5 737 0` (each on a new line).

**Output:** Identical to the MutantStack test — proving that `MutantStack` behaves exactly like an iterable container.

---

### Test 3: Reverse Iterators (lines 65–83)

```cpp
MutantStack<int> mstack;
mstack.push(1);  // c = [1]
mstack.push(2);  // c = [1, 2]
mstack.push(3);  // c = [1, 2, 3]
mstack.push(4);  // c = [1, 2, 3, 4]
mstack.push(5);  // c = [1, 2, 3, 4, 5]
```

#### Forward iteration

```cpp
for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it)
    std::cout << *it << " ";
```

Traverses from `begin()` (element 1) to `end()` (past element 5):

```
1 → 2 → 3 → 4 → 5
```

**Output:** `Forward:  1 2 3 4 5`

#### Reverse iteration

```cpp
for (MutantStack<int>::reverse_iterator rit = mstack.rbegin(); rit != mstack.rend(); ++rit)
    std::cout << *rit << " ";
```

`rbegin()` calls `this->c.rbegin()` — returns a reverse iterator starting at the **last element** (5).
`rend()` calls `this->c.rend()` — returns a reverse iterator pointing before the **first element**.

`++rit` moves **backward** through the container:

```
5 → 4 → 3 → 2 → 1
```

**Output:** `Reverse:  5 4 3 2 1`

```
Visual of iterator positions:

  Elements:    [  1  |  2  |  3  |  4  |  5  ]
  
  Forward:   begin→ ──────────────────────→ end
  Reverse:   rend ←──────────────────────← rbegin
```

---

### Test 4: Empty Stack Iteration (lines 85–95)

```cpp
MutantStack<int> mstack;
std::cout << "Size: " << mstack.size() << std::endl;
```
- `size()` → `c.size()` → 0
- **Output:** `Size: 0`

```cpp
std::cout << "Empty: " << (mstack.empty() ? "yes" : "no") << std::endl;
```
- `empty()` → `c.empty()` → true
- The ternary `? :` returns `"yes"`
- **Output:** `Empty: yes`

```cpp
MutantStack<int>::iterator it = mstack.begin();
MutantStack<int>::iterator ite = mstack.end();
if (it == ite)
    std::cout << "begin == end (empty stack OK)" << std::endl;
```
- On an empty deque, `begin() == end()` → true
- **Output:** `begin == end (empty stack OK)`

This proves that iterating over an empty MutantStack is safe — the loop `while (it != ite)` simply never executes.

---

### Test 5: MutantStack with Strings (lines 97–107)

```cpp
MutantStack<std::string> mstack;
```

The compiler now instantiates **an entirely new version** of `MutantStack` with `T = std::string`:
- `std::stack<std::string>` is the base
- Its `c` is a `std::deque<std::string>`
- Iterators traverse `std::string` elements

```cpp
mstack.push("hello");  // c = ["hello"]
mstack.push("world");  // c = ["hello", "world"]
mstack.push("42");     // c = ["hello", "world", "42"]
```

Note: `"hello"` is a `const char*` (C string literal), but `push()` expects `const std::string&`. The compiler calls `std::string`'s **implicit conversion constructor** `std::string(const char*)` to create a temporary `std::string`, which is then pushed.

```cpp
for (MutantStack<std::string>::iterator it = mstack.begin(); it != mstack.end(); ++it)
    std::cout << *it << " ";
std::cout << std::endl;
```

Iterates through the deque:
```
"hello" → "world" → "42"
```

**Output:** `hello world 42`

---

## Part 3: Complete Expected Output

```
=== Subject test (MutantStack) ===
17
1
5
3
5
737
0

=== Same test with std::list ===
17
1
5
3
5
737
0

=== Test: reverse iterators ===
Forward:  1 2 3 4 5 
Reverse:  5 4 3 2 1 

=== Test: empty stack iteration ===
Size: 0
Empty: yes
begin == end (empty stack OK)

=== Test: MutantStack with strings ===
hello world 42 
```

---

## Part 4: Summary — What This Exercise Teaches

| Concept | What you learned |
|---------|-----------------|
| **Container adapter** | `std::stack` is not a container — it wraps a `std::deque` and restricts its interface to LIFO operations |
| **Protected member `c`** | `std::stack` stores its deque as `protected` → derived classes can access it to expose iterators |
| **Template inheritance** | `MutantStack<T>` inherits from `std::stack<T>` — propagating the type parameter to the base |
| **`this->` in templates** | Required to access base class members when the base depends on a template parameter |
| **`container_type`** | A typedef inside `std::stack` that reveals the underlying container's type (`std::deque<T>`) |
| **`typedef` for nested types** | Creates user-friendly aliases like `MutantStack::iterator` instead of `std::deque<int>::iterator` |
| **Reverse iterators** | `rbegin()`/`rend()` traverse the container backwards; `++rit` moves toward the front |
| **Const iterators** | `const_iterator` prevents modification through the iterator — used for const-correct code |
| **Object slicing** | Copying a `MutantStack` into a `std::stack` drops the derived class's methods |
| **Implicit conversion** | `const char*` → `std::string` via implicit constructor call when pushing string literals |
