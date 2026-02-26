#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include "easyfind.hpp"

int main() {
	std::cout << "=== Test 1: vector of ints ===" << std::endl;
	{
		std::vector<int> v;
		v.push_back(10);
		v.push_back(20);
		v.push_back(30);
		v.push_back(40);
		v.push_back(50);

		try {
			std::vector<int>::iterator it = easyfind(v, 30);
			std::cout << "Found: " << *it << std::endl;
		} catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}

		try {
			std::vector<int>::iterator it = easyfind(v, 42);
			std::cout << "Found: " << *it << std::endl;
		} catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}

	std::cout << std::endl << "=== Test 2: list of ints ===" << std::endl;
	{
		std::list<int> lst;
		lst.push_back(1);
		lst.push_back(2);
		lst.push_back(3);
		lst.push_back(4);
		lst.push_back(5);

		try {
			std::list<int>::iterator it = easyfind(lst, 1);
			std::cout << "Found: " << *it << std::endl;
		} catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}

		try {
			std::list<int>::iterator it = easyfind(lst, 5);
			std::cout << "Found: " << *it << std::endl;
		} catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}

		try {
			std::list<int>::iterator it = easyfind(lst, 99);
			std::cout << "Found: " << *it << std::endl;
		} catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}

	std::cout << std::endl << "=== Test 3: deque of ints ===" << std::endl;
	{
		std::deque<int> dq;
		dq.push_back(-1);
		dq.push_back(0);
		dq.push_back(1);

		try {
			std::deque<int>::iterator it = easyfind(dq, 0);
			std::cout << "Found: " << *it << std::endl;
		} catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}

		try {
			std::deque<int>::iterator it = easyfind(dq, -1);
			std::cout << "Found: " << *it << std::endl;
		} catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}

	std::cout << std::endl << "=== Test 4: empty container ===" << std::endl;
	{
		std::vector<int> empty;

		try {
			std::vector<int>::iterator it = easyfind(empty, 1);
			std::cout << "Found: " << *it << std::endl;
		} catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}

	std::cout << std::endl << "=== Test 5: duplicate values (finds first) ===" << std::endl;
	{
		std::vector<int> v;
		v.push_back(5);
		v.push_back(10);
		v.push_back(5);
		v.push_back(20);

		try {
			std::vector<int>::iterator it = easyfind(v, 5);
			std::cout << "Found: " << *it << " at index " << (it - v.begin()) << std::endl;
		} catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}

	return 0;
}