# CPP Module 09 Reading Plan

- [x] Read PDF Page 1 (General Rules and Introduction)
- [x] Read PDF Page 2 (Exercise 00: Bitcoin Exchange)
- [x] Read PDF Page 3 (Exercise 01: Reverse Polish Notation)
- [x] Read PDF Page 4 (Exercise 02: PmergeMe)
- [x] Read PDF Page 5 (Continuation of Exercise 02 or Conclusion)
- [x] Compile full explanation for each exercise
- [x] Identify learning goals and roadmap

## Summary of Findings

### General Rules
- C++98, Makefile, Orthodox Canonical Form.
- STL Containers and Algorithms allowed.
- Forbidden: `printf`, `alloc`, `free`, `using namespace`, `friend`.

### Exercise 00: Bitcoin Exchange
- Files: `BitcoinExchange.{cpp, hpp}`, `main.cpp`, `Makefile`.
- Use a `data.csv` for prices.
- Match input dates to prices (use closest lower date if missing).
- Values [0, 1000]. Date YYYY-MM-DD.
- Container recommendation: `std::map`.

### Exercise 01: RPN
- Files: `RPN.{cpp, hpp}`, `main.cpp`, `Makefile`.
- Evaluate RPN expression from string argument.
- Numbers < 10. Operators: `+ - / *`.
- Container recommendation: `std::stack`.

### Exercise 02: PmergeMe
- Files: `PmergeMe.{cpp, hpp}`, `main.cpp`, `Makefile`.
- Sort positive integers using Ford-Johnson algorithm.
- Must use at least 2 different containers.
- Display time for each.
- Handle 3000+ integers.

## Learning Roadmap
1. **Ex00**: Map, File I/O, Date validation.
2. **Ex01**: Stack, Expression parsing.
3. **Ex02**: Ford-Johnson algorithm, Vector/Deque comparison, Performance timing.
