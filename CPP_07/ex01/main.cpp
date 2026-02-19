#include <iostream>
#include <string>
#include "iter.hpp"

void	printInt(int const &n)
{
	std::cout << n << std::endl;
}

void	printString(std::string const &s)
{
	std::cout << s << std::endl;
}

void	doubleIt(int &n)
{
	n *= 2;
}

void	toUpper(std::string &s)
{
	for (size_t i = 0; i < s.size(); i++)
		s[i] = static_cast<char>(std::toupper(s[i]));
}

int	main(void)
{
	// --- Test with int array (non-const) ---
	std::cout << "=== int array ===" << std::endl;
	int	intArr[] = {1, 2, 3, 4, 5};
	iter(intArr, 5, printInt);

	// --- Test mutation via non-const reference ---
	std::cout << "=== int array after doubling ===" << std::endl;
	iter(intArr, 5, doubleIt);
	iter(intArr, 5, printInt);

	// --- Test with const int array ---
	std::cout << "=== const int array ===" << std::endl;
	int const	constArr[] = {10, 20, 30};
	iter(constArr, 3, printInt);

	// --- Test with std::string array ---
	std::cout << "=== string array ===" << std::endl;
	std::string	strArr[] = {"hello", "world", "cpp07"};
	iter(strArr, 3, printString);

	// --- Test mutation on string array ---
	std::cout << "=== string array after toUpper ===" << std::endl;
	iter(strArr, 3, toUpper);
	iter(strArr, 3, printString);

	// --- Test with const string array ---
	std::cout << "=== const string array ===" << std::endl;
	std::string const	constStrArr[] = {"foo", "bar", "baz"};
	iter(constStrArr, 3, printString);

	return 0;
}
