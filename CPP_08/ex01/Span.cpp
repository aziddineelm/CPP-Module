#include "Span.hpp"
#include <limits>

Span::Span() : _maxSize(0) {}

Span::Span(unsigned int n) : _maxSize(n) {}

Span::Span(const Span& other) : _maxSize(other._maxSize), _numbers(other._numbers) {}

Span& Span::operator=(const Span& other) {
	if (this != &other) {
		_maxSize = other._maxSize;
		_numbers = other._numbers;
	}
	return *this;
}

Span::~Span() {}

void Span::addNumber(int number) {
	if (_numbers.size() >= _maxSize)
		throw SpanFullException();
	_numbers.push_back(number);
}

int Span::shortestSpan() const {
	if (_numbers.size() < 2)
		throw NoSpanException();

	std::vector<int> sorted(_numbers);
	std::sort(sorted.begin(), sorted.end());

	int minSpan = sorted[1] - sorted[0];
	for (std::vector<int>::size_type i = 2; i < sorted.size(); ++i) {
		int diff = sorted[i] - sorted[i - 1];
		if (diff < minSpan)
			minSpan = diff;
	}
	return minSpan;
}

int Span::longestSpan() const {
	if (_numbers.size() < 2)
		throw NoSpanException();

	int min = *std::min_element(_numbers.begin(), _numbers.end());
	int max = *std::max_element(_numbers.begin(), _numbers.end());
	return max - min;
}

const char* Span::SpanFullException::what() const throw() {
	return "Cannot add number: Span is full";
}

const char* Span::NoSpanException::what() const throw() {
	return "Cannot find span: not enough numbers stored";
}
