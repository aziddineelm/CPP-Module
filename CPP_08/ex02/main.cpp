#include <iostream>
#include <list>
#include "MutantStack.hpp"

int main() {
	std::cout << "=== Subject test (MutantStack) ===" << std::endl;
	{
		MutantStack<int> mstack;

		mstack.push(5);
		mstack.push(17);

		std::cout << mstack.top() << std::endl;

		mstack.pop();

		std::cout << mstack.size() << std::endl;

		mstack.push(3);
		mstack.push(5);
		mstack.push(737);
		mstack.push(0);

		MutantStack<int>::iterator it = mstack.begin();
		MutantStack<int>::iterator ite = mstack.end();

		++it;
		--it;
		while (it != ite) {
			std::cout << *it << std::endl;
			++it;
		}
		std::stack<int> s(mstack);
	}

	std::cout << std::endl << "=== Same test with std::list ===" << std::endl;
	{
		std::list<int> mstack;

		mstack.push_back(5);
		mstack.push_back(17);

		std::cout << mstack.back() << std::endl;

		mstack.pop_back();

		std::cout << mstack.size() << std::endl;

		mstack.push_back(3);
		mstack.push_back(5);
		mstack.push_back(737);
		mstack.push_back(0);

		std::list<int>::iterator it = mstack.begin();
		std::list<int>::iterator ite = mstack.end();

		++it;
		--it;
		while (it != ite) {
			std::cout << *it << std::endl;
			++it;
		}
	}

	std::cout << std::endl << "=== Test: reverse iterators ===" << std::endl;
	{
		MutantStack<int> mstack;
		mstack.push(1);
		mstack.push(2);
		mstack.push(3);
		mstack.push(4);
		mstack.push(5);

		std::cout << "Forward:  ";
		for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;

		std::cout << "Reverse:  ";
		for (MutantStack<int>::reverse_iterator rit = mstack.rbegin(); rit != mstack.rend(); ++rit)
			std::cout << *rit << " ";
		std::cout << std::endl;
	}

	std::cout << std::endl << "=== Test: empty stack iteration ===" << std::endl;
	{
		MutantStack<int> mstack;
		std::cout << "Size: " << mstack.size() << std::endl;
		std::cout << "Empty: " << (mstack.empty() ? "yes" : "no") << std::endl;

		MutantStack<int>::iterator it = mstack.begin();
		MutantStack<int>::iterator ite = mstack.end();
		if (it == ite)
			std::cout << "begin == end (empty stack OK)" << std::endl;
	}

	std::cout << std::endl << "=== Test: MutantStack with strings ===" << std::endl;
	{
		MutantStack<std::string> mstack;
		mstack.push("hello");
		mstack.push("world");
		mstack.push("42");

		for (MutantStack<std::string>::iterator it = mstack.begin(); it != mstack.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
	}

	return 0;
}
