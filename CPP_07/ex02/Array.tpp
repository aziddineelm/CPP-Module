#ifndef ARRAY_TPP
# define ARRAY_TPP

# include "Array.hpp"

template <typename T>
Array<T>::Array() : _data(0), _size(0) {}

template <typename T>
Array<T>::Array(unsigned int n) : _data(new T[n]()), _size(n) {}

template <typename T>
Array<T>::Array(const Array& other) : _data(0), _size(0)
{
	*this = other;
}

template <typename T>
Array<T>::~Array()
{
	delete[] _data;
}

template <typename T>
Array<T>& Array<T>::operator=(const Array& other)
{
	if (this == &other)
		return *this;

	T* new_data = new T[other._size]();
	for (unsigned int i = 0; i < other._size; i++)
		new_data[i] = other._data[i];
	delete[] _data;
	_data = new_data;
	_size = other._size;

	return *this;
}

template <typename T>
T& Array<T>::operator[](unsigned int index)
{
	if (index >= _size)
		throw std::out_of_range("Array: index out of bounds");
	return _data[index];
}

template <typename T>
const T& Array<T>::operator[](unsigned int index) const
{
	if (index >= _size)
		throw std::out_of_range("Array: index out of bounds");
	return _data[index];
}

template <typename T>
unsigned int Array<T>::getSize() const
{
	return _size;
}

#endif
