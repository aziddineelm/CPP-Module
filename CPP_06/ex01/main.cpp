#include "Serializer.hpp"
#include <iostream>

int main() {
	// Create a Data object with some values
	Data originalData;
	originalData.name = "TestObject";
	originalData.value = 42;
	originalData.coefficient = 3.14159;
	originalData.isActive = true;
	originalData.category = 'A';

	// Display original data
	std::cout << "=== Original Data ===" << std::endl;
	std::cout << "Address:      " << &originalData << std::endl;
	std::cout << "Name:         " << originalData.name << std::endl;
	std::cout << "Value:        " << originalData.value << std::endl;
	std::cout << "Coefficient:  " << originalData.coefficient << std::endl;
	std::cout << "IsActive:     " << (originalData.isActive ? "true" : "false") << std::endl;
	std::cout << "Category:     " << originalData.category << std::endl;
	std::cout << std::endl;

	// Serialize the pointer
	uintptr_t serialized = Serializer::serialize(&originalData);
	std::cout << "=== Serialization ===" << std::endl;
	std::cout << "Serialized:   " << serialized << " (0x" << std::hex << serialized << std::dec << ")" << std::endl;
	std::cout << std::endl;

	// Deserialize back to pointer
	Data* deserialized = Serializer::deserialize(serialized);
	std::cout << "=== Deserialization ===" << std::endl;
	std::cout << "Address:      " << deserialized << std::endl;
	std::cout << "Name:         " << deserialized->name << std::endl;
	std::cout << "Value:        " << deserialized->value << std::endl;
	std::cout << "Coefficient:  " << deserialized->coefficient << std::endl;
	std::cout << "IsActive:     " << (deserialized->isActive ? "true" : "false") << std::endl;
	std::cout << "Category:     " << deserialized->category << std::endl;
	std::cout << std::endl;

	// Verify pointers are equal
	std::cout << "=== Verification ===" << std::endl;
	if (deserialized == &originalData) {
		std::cout << "✓ Success: Deserialized pointer matches original pointer!" << std::endl;
		std::cout << "  Original:      " << &originalData << std::endl;
		std::cout << "  Deserialized:  " << deserialized << std::endl;
	} else {
		std::cout << "✗ Error: Pointers do not match!" << std::endl;
	}
	std::cout << std::endl;

	// Additional test with different data
	std::cout << "=== Additional Test ===" << std::endl;
	Data secondData;
	secondData.name = "SecondObject";
	secondData.value = -100;
	secondData.coefficient = 2.71828;
	secondData.isActive = false;
	secondData.category = 'Z';

	uintptr_t serialized2 = Serializer::serialize(&secondData);
	Data* deserialized2 = Serializer::deserialize(serialized2);

	std::cout << "Original address:     " << &secondData << std::endl;
	std::cout << "Deserialized address: " << deserialized2 << std::endl;
	std::cout << "Match: " << (deserialized2 == &secondData ? "✓ Yes" : "✗ No") << std::endl;
	std::cout << "Accessed value: " << deserialized2->value << std::endl;

	return 0;
}
