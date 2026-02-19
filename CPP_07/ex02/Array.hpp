#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <stdexcept>

template <typename T>
class Array
{
	private:
		T*				_data;
		unsigned int    _size;

	public:

		// ── Constructors / Destructor ─────────────────────────────────────

		// Default: empty array
		Array() : _data(0), _size(0) {}

		// Parameterized: allocate n default-initialised elements
		Array(unsigned int n) : _data(new T[n]()), _size(n) {}

		// Copy constructor: deep copy
		Array(const Array& other) : _data(0), _size(0)
		{
			*this = other;
		}

		// Destructor: release heap memory
		~Array()
		{
			delete[] _data;
		}

		// ── Copy assignment operator: deep copy ───────────────────────────

		Array& operator=(const Array& other)
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

		// ── Element access ────────────────────────────────────────────────

		// Non-const overload
		T& operator[](unsigned int index)
		{
			if (index >= _size)
				throw std::out_of_range("Array: index out of bounds");
			return _data[index];
		}

		// Const overload (read-only access)
		const T& operator[](unsigned int index) const
		{
			if (index >= _size)
			throw std::out_of_range("Array: index out of bounds");
			return _data[index];
		}

		// ── Size query ────────────────────────────────────────────────────

		unsigned int size() const
		{
			return _size;
		}
};

#endif