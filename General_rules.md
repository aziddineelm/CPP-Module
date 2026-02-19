# C++ Module - General Rules

## Compiling

- Compile your code with `c++` and the flags `-Wall -Wextra -Werror`
- Your code should still compile if you add the flag `-std=c++98`

## Formatting and Naming Conventions

- The exercise directories will be named this way: `ex00`, `ex01`, ..., `exn`

- Name your files, classes, functions, member functions and attributes as required in the guidelines.

- Write class names in **UpperCamelCase** format. Files containing class code will always be named according to the class name. For instance:
  - `ClassName.hpp`/`ClassName.h`
  - `ClassName.cpp`
  - `ClassName.tpp`
  
  If you have a header file containing the definition of a class "BrickWall" standing for a brick wall, its name will be `BrickWall.hpp`.

- Unless specified otherwise, every output message must end with a newline character and be displayed to the standard output.

## Allowed/Forbidden

You are not coding in C anymore. Time to C++! Therefore:

- You are allowed to use almost everything from the standard library. Thus, instead of sticking to what you already know, it would be smart to use the C++-ish versions of the C functions you are used to as much as possible.

- However, you can't use any other external library. It means **C++11** (and derived forms) and **Boost libraries** are forbidden. The following functions are forbidden too: `*printf()`, `*alloc()` and `free()`. If you use them, your grade will be 0 and that's it.

- Note that unless explicitly stated otherwise, the `using namespace <ns_name>` and `friend` keywords are forbidden. Otherwise, your grade will be -42.

- You are allowed to use the **STL only in Modules 08 and 09**. That means: no Containers (vector/list/map, and so forth) and no Algorithms (anything that requires including the `<algorithm>` header) until then. Otherwise, your grade will be -42.

## Design Requirements

- Memory leakage occurs in C++ too. When you allocate memory (by using the `new` keyword), you must avoid memory leaks.

- From Module 02 to Module 09, your classes must be designed in the **Orthodox Canonical Form**, except when explicitly stated otherwise.

- Any function implementation put in a header file (except for function templates) means 0 to the exercise.

- You should be able to use each of your headers independently from others. Thus, they must include all the dependencies they need. However, you must avoid the problem of double inclusion by adding **include guards**. Otherwise, your grade will be 0.

## Read Me

- You can add some additional files if you need to (i.e., to split your code). As these assignments are not verified by a program, feel free to do so as long as you turn in the mandatory files.

- Sometimes, the guidelines of an exercise look short but the examples can show requirements that are not explicitly written in the instructions.

- **Read each module completely before starting!** Really, do it.

## New rules
- From now on, all your classes must be designed in the Orthodox Canonical Form,
unless explicitly stated otherwise. They will then implement the four required member
functions below:
-  Default constructor
-  Copy constructor
-  Copy assignment operator
-  Destructor
- Split your class code into two files. The header file (.hpp/.h) contains the class
definition, whereas the source file (.cpp) contains the implementation.