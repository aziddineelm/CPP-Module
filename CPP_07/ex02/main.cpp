#include <iostream>
#include <string>
#include "Array.hpp"

int main(void)
{
	std::cout << "=== Default constructor (empty array) ===" << std::endl;
	Array<int> empty;
	std::cout << "Size: " << empty.getSize() << std::endl;

	std::cout << "\n=== Parameterized constructor ===" << std::endl;
	Array<int> intArr(5);
	std::cout << "Size: " << intArr.getSize() << std::endl;
	std::cout << "Default values: ";
	for (unsigned int i = 0; i < intArr.getSize(); i++)
		std::cout << intArr[i] << " ";
	std::cout << std::endl;

	std::cout << "\n=== Assigning values ===" << std::endl;
	for (unsigned int i = 0; i < intArr.getSize(); i++)
		intArr[i] = (i + 1) * 10;
	for (unsigned int i = 0; i < intArr.getSize(); i++)
		std::cout << intArr[i] << " ";
	std::cout << std::endl;

	std::cout << "\n=== Copy constructor (deep copy) ===" << std::endl;
	Array<int> copyArr(intArr);
	std::cout << "Copy: ";
	for (unsigned int i = 0; i < copyArr.getSize(); i++)
		std::cout << copyArr[i] << " ";
	std::cout << std::endl;

	copyArr[0] = 1337;
	std::cout << "After modifying copy[0] = 1337:" << std::endl;
	std::cout << "Original[0]: " << intArr[0] << std::endl;
	std::cout << "Copy[0]: " << copyArr[0] << std::endl;

	std::cout << "\n=== Assignment operator (deep copy) ===" << std::endl;
	Array<int> assignArr(2);
	assignArr = intArr;
	std::cout << "Assigned array size: " << assignArr.getSize() << std::endl;
	
	assignArr[0] = 1337;
	std::cout << "After modifying assignArr[0] = 1337:" << std::endl;
	std::cout << "Original[0]: " << intArr[0] << std::endl;
	std::cout << "Assigned[0]: " << assignArr[0] << std::endl;

	std::cout << "\n=== Out of bounds exception ===" << std::endl;
	try {
		std::cout << intArr[100] << std::endl;
	} catch (std::exception &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Access on empty array ===" << std::endl;
	try {
		std::cout << empty[0] << std::endl;
	} catch (std::exception &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Const array test ===" << std::endl;
	const Array<int> constArr(intArr);
	std::cout << "Const array [0]: " << constArr[0] << std::endl;

	std::cout << "\n=== String array ===" << std::endl;
	Array<std::string> strArr(3);
	strArr[0] = "Hello";
	strArr[1] = "World";
	strArr[2] = "42";
	for (unsigned int i = 0; i < strArr.getSize(); i++)
		std::cout << strArr[i] << " ";
	std::cout << std::endl;

	return 0;
}