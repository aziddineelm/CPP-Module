#include <climits>
#include <iostream>
#include <vector>
#include <list>
#include <cstdlib>
#include "Span.hpp"

int main() {
	std::cout << "=== Subject test ===" << std::endl;
	{
		Span sp = Span(5);

		sp.addNumber(6);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);

		std::cout << sp.shortestSpan() << std::endl;
		std::cout << sp.longestSpan() << std::endl;
	}

	std::cout << std::endl << "=== Test: Span full exception ===" << std::endl;
	{
		Span sp(3);
		try {
			sp.addNumber(1);
			sp.addNumber(2);
			sp.addNumber(3);
			sp.addNumber(4);
		} catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}

	std::cout << std::endl << "=== Test: No span (empty) ===" << std::endl;
	{
		Span sp(5);
		try {
			std::cout << sp.shortestSpan() << std::endl;
		} catch (std::exception& e) {
			std::cout << "shortestSpan: " << e.what() << std::endl;
		}
		try {
			std::cout << sp.longestSpan() << std::endl;
		} catch (std::exception& e) {
			std::cout << "longestSpan: " << e.what() << std::endl;
		}
	}

	std::cout << std::endl << "=== Test: No span (one element) ===" << std::endl;
	{
		Span sp(5);
		sp.addNumber(42);
		try {
			std::cout << sp.shortestSpan() << std::endl;
		} catch (std::exception& e) {
			std::cout << "shortestSpan: " << e.what() << std::endl;
		}
		try {
			std::cout << sp.longestSpan() << std::endl;
		} catch (std::exception& e) {
			std::cout << "longestSpan: " << e.what() << std::endl;
		}
	}

	std::cout << std::endl << "=== Test: 10,000 numbers ===" << std::endl;
	{
		Span sp(10000);

		std::srand(42);
		for (int i = 0; i < 10000; ++i)
			sp.addNumber(std::rand());

		std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
		std::cout << "Longest span:  " << sp.longestSpan() << std::endl;
	}

	std::cout << std::endl << "=== Test: addRange with vector iterators ===" << std::endl;
	{
		Span sp(5);
		std::vector<int> v;
		v.push_back(100);
		v.push_back(200);
		v.push_back(300);
		v.push_back(400);
		v.push_back(500);

		sp.addRange(v.begin(), v.end());
		std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
		std::cout << "Longest span:  " << sp.longestSpan() << std::endl;
	}

	std::cout << std::endl << "=== Test: addRange with list iterators ===" << std::endl;
	{
		Span sp(4);
		std::list<int> lst;
		lst.push_back(5);
		lst.push_back(3);
		lst.push_back(17);
		lst.push_back(9);

		sp.addRange(lst.begin(), lst.end());
		std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
		std::cout << "Longest span:  " << sp.longestSpan() << std::endl;
	}

	std::cout << std::endl << "=== Test: addRange overflow ===" << std::endl;
	{
		Span sp(3);
		std::vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		v.push_back(5);

		try {
			sp.addRange(v.begin(), v.end());
		} catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
		std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
		std::cout << "Longest span:  " << sp.longestSpan() << std::endl;
	}

	std::cout << "Test INT_MAX and INT_MIN" << std::endl;
	{
		Span max_min(2);
		std::vector<int> max;
		max.push_back(INT_MAX);
		max.push_back(INT_MIN);
		try {
			max_min.addRange(max.begin(), max.end());
		} catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
		std::cout << "Shortest Span: " << max_min.shortestSpan() << std::endl;
		std::cout << "Longest Span: " << max_min.longestSpan() << std::endl;
	}

	return 0;
}
