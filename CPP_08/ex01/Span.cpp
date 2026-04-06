#include "Span.hpp"
#include <limits>

Span::Span() : _maxSize(0) {}

Span::Span(unsigned int n) : _maxSize(n) {}

Span::Span(const Span &other)
    : _maxSize(other._maxSize), _numbers(other._numbers) {}

Span &Span::operator=(const Span &other) {
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

long long Span::shortestSpan() const {
  if (_numbers.size() < 2)
    throw NoSpanException();

  std::vector<int> sorted(_numbers);
  std::sort(sorted.begin(), sorted.end());

  long long minSpan = static_cast<long long>(sorted[1]) - sorted[0];
  for (std::vector<int>::size_type i = 2; i < sorted.size(); ++i) {
    long long diff = static_cast<long long>(sorted[i]) - sorted[i - 1];
    if (diff < minSpan)
      minSpan = diff;
  }
  return minSpan;
}

long long Span::longestSpan() const {
  if (_numbers.size() < 2)
    throw NoSpanException();

  long long min = static_cast<long long>(*std::min_element(_numbers.begin(), _numbers.end()));
  long long max = static_cast<long long>(*std::max_element(_numbers.begin(), _numbers.end()));
  return max - min;
}

const char *Span::SpanFullException::what() const throw() {
  return "Cannot add number: Span is full";
}

const char *Span::NoSpanException::what() const throw() {
  return "Cannot find span: not enough numbers stored";
}
