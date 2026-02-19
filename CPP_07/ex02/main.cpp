#include <iostream>
#include <string>
#include "Array.hpp"

static void printSeparator(const std::string& label) {
	std::cout << "\n─── " << label << " ───────────────────────────────────\n";
}

static void testDefaultConstructor() {
	printSeparator("Default constructor");

	Array<int> empty;
	std::cout << "Size of empty array: " << empty.size() << "\n";
}

static void testParameterizedConstructor() {
	printSeparator("Parameterized constructor");

	Array<int> ints(5);
	std::cout << "Size: " << ints.size() << "\n";
	std::cout << "Default-initialised elements (all zeros expected):\n";
	for (unsigned int i = 0; i < ints.size(); i++)
	std::cout << "  ints[" << i << "] = " << ints[i] << "\n";
}

static void testWriteAndRead() {
	printSeparator("Write & read elements");

	Array<std::string> words(3);
	words[0] = "hello";
	words[1] = "world";
	words[2] = "!";

	for (unsigned int i = 0; i < words.size(); i++)
	std::cout << "  words[" << i << "] = " << words[i] << "\n";
}

static void testDeepCopy() {
	printSeparator("Deep copy (copy constructor + assignment)");

	// ── copy constructor ──
	Array<int> original(4);
	for (unsigned int i = 0; i < original.size(); i++)
	original[i] = static_cast<int>(i * 10);

	Array<int> copyConstructed(original);
	copyConstructed[0] = 999;   // must NOT affect original

	std::cout << "original[0]        = " << original[0]        << " (expected 0)\n";
	std::cout << "copyConstructed[0] = " << copyConstructed[0] << " (expected 999)\n";

	// ── assignment operator ──
	Array<int> assigned;
	assigned = original;
	assigned[1] = 888;          // must NOT affect original

	std::cout << "original[1]        = " << original[1]        << " (expected 10)\n";
	std::cout << "assigned[1]        = " << assigned[1]        << " (expected 888)\n";

	// ── self-assignment ──
	Array<int>* ptr = &assigned;
	assigned = *ptr;    // indirect self-assign to silence -Wself-assign warning
	std::cout << "Self-assignment: assigned[1] = " << assigned[1] << " (still 888)\n";
}

static void testConstArray() {
	printSeparator("Const array (read-only access)");

	Array<double> tmp(3);
	tmp[0] = 1.1; tmp[1] = 2.2; tmp[2] = 3.3;

	const Array<double> constArr(tmp);
	for (unsigned int i = 0; i < constArr.size(); i++)
	std::cout << "  constArr[" << i << "] = " << constArr[i] << "\n";
}

static void testOutOfBounds() {
	printSeparator("Out-of-bounds exception");

	Array<int> arr(3);
	// ── index too high ──
	try
	{
		arr[5];
		std::cout << "ERROR: no exception thrown!\n";
	}
	catch (const std::exception& e)
	{
		std::cout << "Caught (index 5 on size-3 array): " << e.what() << "\n";
	}
	// ── empty array ──
	try
	{
		Array<int> empty;
		empty[0];
		std::cout << "ERROR: no exception thrown!\n";
	}
		catch (const std::exception& e)
	{
		std::cout << "Caught (index 0 on empty array): " << e.what() << "\n";
	}
}

int main()
{
	testDefaultConstructor();
	testParameterizedConstructor();
	testWriteAndRead();
	testDeepCopy();
	testConstArray();
	testOutOfBounds();

	std::cout << "\n";
	return 0;
}
