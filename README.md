# 📚 CPP Modules — 42 School

A progressive journey through **C++98** fundamentals to advanced concepts, spanning **10 modules** and **30+ exercises**. Each module introduces new features of the language while building on the foundations of previous ones.

> All code is compiled with `c++ -Wall -Wextra -Werror -std=c++98` and follows the **Orthodox Canonical Form** where required.

![Language](https://img.shields.io/badge/Language-C-blue)
![42 Project](https://img.shields.io/badge/42-Project-orange)
![Status](https://img.shields.io/badge/Status-Completed-success)

---

## 🗂️ Table of Contents

| Module | Topic | Exercises |
|--------|-------|-----------|
| [CPP 00](#-cpp-module-00--namespaces-classes--member-functions) | Namespaces, Classes & Member Functions | 3 |
| [CPP 01](#-cpp-module-01--memory-allocation-pointers--references) | Memory Allocation, Pointers & References | 7 |
| [CPP 02](#-cpp-module-02--adhoc-polymorphism--operator-overloading) | Ad-hoc Polymorphism & Operator Overloading | 3 |
| [CPP 03](#-cpp-module-03--inheritance) | Inheritance | 3 |
| [CPP 04](#-cpp-module-04--subtype-polymorphism--abstract-classes) | Subtype Polymorphism & Abstract Classes | 3 |
| [CPP 05](#-cpp-module-05--exceptions) | Exceptions | 4 |
| [CPP 06](#-cpp-module-06--c-type-casting) | C++ Type Casting | 3 |
| [CPP 07](#-cpp-module-07--c-templates) | C++ Templates | 3 |
| [CPP 08](#-cpp-module-08--templated-containers-iterators--algorithms) | Templated Containers, Iterators & Algorithms | 3 |
| [CPP 09](#-cpp-module-09--stl) | STL | 3 |

---

## 📗 CPP Module 00 — Namespaces, Classes & Member Functions

> Introduction to the basics of C++ — classes, instances, member functions, I/O streams, and initialization lists.

### ex00 · Megaphone
A simple program that converts all command-line arguments to **uppercase** and prints them to stdout. Demonstrates basic I/O with `std::cout` and character manipulation.

```
./megaphone "shhhhh... I think the students are asleep..."
SHHHHH... I THINK THE STUDENTS ARE ASLEEP...
```

### ex01 · My Awesome PhoneBook
An interactive **phonebook** program that stores up to 8 contacts in a `PhoneBook` class. Features:
- `ADD` — prompts for contact info (first name, last name, nickname, phone, secret)
- `SEARCH` — displays contacts in a formatted table with field truncation
- `EXIT` — exits the program
- Contacts are stored in a fixed-size array; oldest entries are overwritten when full

**Key classes:** `PhoneBook`, `Contact`

### ex02 · The Job of Your Dreams
Reconstruction of the `Account` class to match the provided `Account.hpp` header and expected log output. Implements:
- Static members tracking total accounts, amounts, deposits, and withdrawals
- Timestamped logging (`_displayTimestamp`)
- `makeDeposit()`, `makeWithdrawal()`, `displayStatus()`

---

## 📘 CPP Module 01 — Memory Allocation, Pointers & References

> Understanding stack vs heap, `new`/`delete`, references, pointers to members, and file streams.

### ex00 · BraiiiiiiinnnzzzZ
Demonstrates stack vs heap allocation with a `Zombie` class. Two functions:
- `newZombie()` — allocates a zombie on the **heap** (returns a pointer)
- `randomChump()` — creates a zombie on the **stack** (destroyed at scope end)

### ex01 · Moar Brainz!
Implements `zombieHorde()` — allocates an **array of Zombie objects** on the heap using `new[]`, then sets their names. Demonstrates dynamic array allocation.

### ex02 · HI THIS IS BRAIN
A short program illustrating the relationship between a **string variable**, a **pointer**, and a **reference** — all pointing to the same memory address.

### ex03 · Unnecessary Violence
Demonstrates the difference between **references and pointers** through weapon-wielding characters:
- `HumanA` — takes a `Weapon&` reference (always armed)
- `HumanB` — takes a `Weapon*` pointer (can be unarmed, weapon is optional)

**Key classes:** `Weapon`, `HumanA`, `HumanB`

### ex04 · Sed is for Losers
A file string-replacement program (reimplementing a basic `sed`). Takes 3 arguments: `<filename>`, `<s1>`, `<s2>`. Reads the file, replaces every occurrence of `s1` with `s2` using `std::string::find`, `erase`, and `insert` (no `std::string::replace`), and writes the result to `<filename>.replace`.

### ex05 · Harl 2.0
Implementation of the `Harl` class with four complaint levels — `DEBUG`, `INFO`, `WARNING`, `ERROR` — dispatched via an array of **pointers to member functions**.

### ex06 · Harl Filter
Extension of Harl with a `switch`/case **filter**: given a minimum level, it displays that level and all levels above it (fall-through behavior).

---

## 📙 CPP Module 02 — Ad-hoc Polymorphism & Operator Overloading

> Fixed-point arithmetic, the Orthodox Canonical Form, and operator overloading.

### ex00 · My First Class in Orthodox Canonical Form
Introduction of the `Fixed` class representing a **fixed-point number**:
- Orthodox Canonical Form: default constructor, copy constructor, copy assignment operator, destructor
- Private `_value` (int) and static `_fractionalBits = 8`
- `getRawBits()` / `setRawBits()`

### ex01 · Towards a More Useful Fixed-Point Number Class
Extends `Fixed` with:
- Constructors from `int` and `float`
- `toFloat()` and `toInt()` conversion methods
- Overloaded `<<` operator for `std::ostream` output

### ex02 · Now We're Talking
Full operator overloading for the `Fixed` class:
- **Comparison**: `>`, `<`, `>=`, `<=`, `==`, `!=`
- **Arithmetic**: `+`, `-`, `*`, `/`
- **Increment/Decrement**: pre/post `++` and `--`
- **Static**: `min()` and `max()` (both mutable and const versions)

---

## 📕 CPP Module 03 — Inheritance

> Class inheritance hierarchies, base/derived classes, and constructor/destructor chaining.

### ex00 · Aaaaand… OPEN!
Implementation of `ClapTrap` — a base class with:
- Attributes: `name`, `hitPoints (10)`, `energyPoints (10)`, `attackDamage (0)`
- Methods: `attack()`, `takeDamage()`, `beRepaired()`
- Orthodox Canonical Form

### ex01 · Serena, My Love!
`ScavTrap` inherits from `ClapTrap`:
- Overridden default stats: `hitPoints (100)`, `energyPoints (50)`, `attackDamage (20)`
- Overridden `attack()` with custom message
- New method: `guardGate()` — displays Gate keeper mode

### ex02 · Repetitive Work
`FragTrap` also inherits from `ClapTrap`:
- Overridden default stats: `hitPoints (100)`, `energyPoints (100)`, `attackDamage (30)`
- Overridden `attack()` with custom message
- New method: `highFivesGuys()` — positive high fives request

---

## 📓 CPP Module 04 — Subtype Polymorphism & Abstract Classes

> Virtual functions, pure virtual functions, abstract classes, and deep copy semantics.

### ex00 · Polymorphism
An `Animal` base class with `Cat` and `Dog` derived classes:
- `virtual makeSound()` — demonstrates runtime polymorphism
- `WrongAnimal` / `WrongCat` — shows what happens **without** virtual functions (no polymorphic behavior)

### ex01 · I Don't Want to Set the World on Fire
Adds a `Brain` class (stores 100 `ideas` as strings):
- `Cat` and `Dog` each have a private `Brain*` member
- Demonstrates **deep copy**: copy constructor and assignment operator clone the Brain
- Proper cleanup: destructors `delete` the Brain to prevent leaks

### ex02 · Abstract Class
Makes `Animal` an **abstract class** by declaring `makeSound()` as a **pure virtual function** (`= 0`), preventing direct instantiation of `Animal`.

---

## 📒 CPP Module 05 — Exceptions

> Custom exception classes, try/catch blocks, and building a form-processing bureaucracy system.

### ex00 · Mommy, When I Grow Up, I Want to Be a Bureaucrat!
`Bureaucrat` class with:
- `const name` and `grade` (1–150, where 1 is the highest)
- `incrementGrade()` / `decrementGrade()`
- Nested exceptions: `GradeTooHighException`, `GradeTooLowException`
- Overloaded `<<` operator: `<name>, bureaucrat grade <grade>`

### ex01 · Form Up, Maggots!
`Form` class with:
- `const name`, `isSigned` flag, `gradeToSign`, `gradeToExecute`
- `beSigned()` — throws `GradeTooLowException` if the bureaucrat's grade is too low
- `Bureaucrat::signForm()` — logs signing success/failure

### ex02 · No, You Need Form 28B, Not 28C…
Abstract base class `AForm` with three concrete form types:
- **`ShrubberyCreationForm`** — writes ASCII trees to `<target>_shrubbery`
- **`RobotomyRequestForm`** — 50% chance of successful robotomy
- **`PresidentialPardonForm`** — pardons the target by Zaphod Beeblebrox
- Execution requires the form to be signed and the executor's grade to be sufficient

### ex03 · At Least This Is Not Coffee That Makes Itself
`Intern` class with a `makeForm()` factory method:
- Takes a form name and target, dynamically creates the appropriate `AForm*`
- Supports: `"shrubbery creation"`, `"robotomy request"`, `"presidential pardon"`
- Avoids if/else chains using an array of form types and function pointers

---

## 📔 CPP Module 06 — C++ Type Casting

> `static_cast`, `dynamic_cast`, `reinterpret_cast` — the C++ casting operators.

### ex00 · Conversion of Scalar Types
`ScalarConverter` — a non-instantiable class with a static `convert()` method:
- Detects and converts a string literal to `char`, `int`, `float`, and `double`
- Handles pseudo-literals: `-inff`, `+inff`, `nanf`, `-inf`, `+inf`, `nan`
- Handles edge cases (non-displayable chars, overflow, impossible conversions)

### ex01 · Serialization
`Serializer` — a non-instantiable class demonstrating `reinterpret_cast`:
- `serialize(Data* ptr)` → converts a pointer to `uintptr_t`
- `deserialize(uintptr_t raw)` → converts back to `Data*`
- Proves round-trip serialization preserves the original pointer

**`Data` struct** contains: `name`, `value`, `coefficient`, `isActive`, `category`

### ex02 · Identify Real Type
Dynamic type identification at runtime:
- `Base` class with virtual destructor; `A`, `B`, `C` inherit from it
- `generate()` — randomly instantiates one of A, B, or C
- `identify(Base* p)` — identifies type using `dynamic_cast` with pointers
- `identify(Base& p)` — identifies type using `dynamic_cast` with references and `try/catch`

---

## 📃 CPP Module 07 — C++ Templates

> Function templates and class templates.

### ex00 · Start With a Few Functions
Three template functions in `whatever.hpp`:
- `swap(a, b)` — swaps two values
- `min(a, b)` — returns the smaller value (returns b if equal)
- `max(a, b)` — returns the larger value (returns b if equal)

### ex01 · Iter
A template function `iter(array, length, func)` that applies a function `func` to every element of an array. Works with **any type** and **any callable** (function pointer or functor).

### ex02 · Array
A template class `Array<T>` that wraps a dynamically allocated C-style array:
- Default constructor (empty array) and parameterized constructor (`Array(n)`)
- Deep copy via copy constructor and assignment operator
- Bounds-checked `operator[]` — throws `std::out_of_range` on invalid access
- `getSize()` member function

---

## 📜 CPP Module 08 — Templated Containers, Iterators & Algorithms

> STL containers, iterators, and the `<algorithm>` header.

### ex00 · Easy Find
A template function `easyfind(container, value)`:
- Searches for an integer in any STL container using `std::find`
- Throws a custom `NotFoundException` if the element is not found
- Works with `std::vector`, `std::list`, `std::deque`, etc.

### ex01 · Span
A `Span` class that stores up to `N` integers in a `std::vector<int>`:
- `addNumber(int)` — adds a single number (throws `SpanFullException` if full)
- `addRange(begin, end)` — template method to add a range of numbers via iterators
- `shortestSpan()` / `longestSpan()` — compute the minimum/maximum difference between any two stored numbers (throws `NoSpanException` if fewer than 2 elements)

### ex02 · MutantStack
A `MutantStack<T>` class that inherits from `std::stack<T>` and exposes **iterators**:
- Provides `begin()`, `end()`, `rbegin()`, `rend()` (and const versions)
- Implemented by accessing the underlying container via `std::stack::c` (the protected member)
- Allows iteration over a stack — something `std::stack` doesn't natively support

---

## 📑 CPP Module 09 — STL

> Deep dive into the Standard Template Library — each exercise **must use a different container** type.

### ex00 · Bitcoin Exchange
`BitcoinExchange` — evaluates Bitcoin values on specific dates:
- Loads a CSV database of historical BTC prices into a **`std::map<string, float>`**
- Parses an input file with `date | value` lines
- Uses `std::map::lower_bound` to find the closest earlier date if exact match is missing
- Robust error handling: invalid dates, negative values, values > 1000, bad formatting

### ex01 · Reverse Polish Notation
`RPN` — evaluates mathematical expressions in Reverse Polish Notation:
- Uses a **`std::stack<long>`** to process tokens
- Supports operators: `+`, `-`, `*`, `/`
- Handles division by zero and malformed expressions
- Operands are restricted to single-digit numbers (0–9)

```
./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
42
```

### ex02 · PmergeMe *(in progress)*
Implementation of the **Ford-Johnson merge-insert sort algorithm** using two different containers. Compares performance by measuring and displaying sort times.

---

## 🛠️ Build & Run

Each exercise contains its own `Makefile`:

```bash
cd CPP_XX/exYY
make          # Compile
./program     # Run (program name varies per exercise)
make clean    # Remove object files
make fclean   # Remove object files + binary
make re       # Full recompile
```

---

## 📐 General Rules

- All code compiled with `c++ -Wall -Wextra -Werror -std=c++98`
- Classes follow the **Orthodox Canonical Form** (default constructor, copy constructor, copy assignment operator, destructor)
- No memory leaks
- Header files include guards (include guards or `#pragma once`)
- No use of `using namespace std;` — explicit `std::` prefix everywhere
- No external libraries (except the C++ standard library)

---

## 👤 Author

**aziddineelm** — [GitHub](https://github.com/aziddineelm)
