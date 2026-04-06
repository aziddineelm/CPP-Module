#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <exception>
#include <algorithm>

class Span {
private:
	unsigned int		_maxSize;
	std::vector<int>	_numbers;

public:
	Span();
	Span(unsigned int n);
	Span(const Span& other);
	Span& operator=(const Span& other);
	~Span();

	void	addNumber(int number);

	template <typename InputIterator>
	void	addRange(InputIterator begin, InputIterator end);

	long long		shortestSpan() const;
	long long		longestSpan() const;

	class SpanFullException : public std::exception {
	public:
		const char* what() const throw();
	};

	class NoSpanException : public std::exception {
	public:
		const char* what() const throw();
	};
};

template <typename InputIterator>
void Span::addRange(InputIterator begin, InputIterator end) {
	while (begin != end) {
		addNumber(*begin);
		++begin;
	}
}

#endif
