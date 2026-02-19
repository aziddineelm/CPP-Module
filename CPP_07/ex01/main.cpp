#include <iostream>
#include <string>
#include <cctype>
#include "iter.hpp"

template <typename T>
void printElement(T const &element) {
    std::cout << element << " ";
}

template <typename T>
void increment(T &element) {
    element++;
}

void toUpper(std::string &str) {
    for (size_t i = 0; i < str.length(); i++) {
        str[i] = static_cast<char>(std::toupper(str[i]));
    }
}

int main(void) {
    std::cout << "=== Int array ===" << std::endl;
    int numbers[] = {42, 84, 16};
    ::iter(numbers, 3, printElement<int>);
    std::cout << std::endl;

    std::cout << "\n=== After increment ===" << std::endl;
    ::iter(numbers, 3, increment<int>);
    ::iter(numbers, 3, printElement<int>);
    std::cout << std::endl;

    std::cout << "\n=== String array ===" << std::endl;
    std::string words[] = {"apple", "banana", "cherry", "date"};
    ::iter(words, 4, printElement<std::string>);
    std::cout << std::endl;

    std::cout << "\n=== After toUpper ===" << std::endl;
    ::iter(words, 4, toUpper);
    ::iter(words, 4, printElement<std::string>);
    std::cout << std::endl;

    std::cout << "\n=== Const int array ===" << std::endl;
    int const readOnlyNums[] = {100, 200, 300};
    ::iter(readOnlyNums, 3, printElement<int const>);
    std::cout << std::endl;

    std::cout << "\n=== Double array ===" << std::endl;
    double decimals[] = {4.2, 8.4, 16.8};
    ::iter(decimals, 3, printElement<double>);
    std::cout << std::endl;

    std::cout << "\n=== Char array ===" << std::endl;
    char letters[] = {'q', 'w', 'e', 'r'};
    ::iter(letters, 4, printElement<char>);
    std::cout << std::endl;

    return 0;
}