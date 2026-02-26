#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <algorithm>
#include <exception>

class NotFoundException : public std::exception {
public:
	const char* what() const throw() {
		return "Element not found in container";
	}
};

template <typename T>
typename T::iterator easyfind(T& container, int n);

#include "easyfind.tpp"

#endif