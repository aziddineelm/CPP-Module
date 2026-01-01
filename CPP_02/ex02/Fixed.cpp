#include "Fixed.hpp"

Fixed::Fixed() : _fixedPointValue(0) {
}

Fixed::Fixed( const int intVal ) {
	this->_fixedPointValue = intVal << _fractionalBits;
}

Fixed::Fixed( const float floatVal ) {
	this->_fixedPointValue = (roundf(floatVal * (1 << _fractionalBits)));
}

Fixed::Fixed( const Fixed& other ) {
	this->_fixedPointValue = other.getRawBits();
}

Fixed& Fixed::operator=( const Fixed& other ) {
	if (this != &other)
		this->_fixedPointValue = other.getRawBits();
	return *this;
}

Fixed::~Fixed() {
}

int Fixed::getRawBits( void ) const {
	return this->_fixedPointValue;
}

void Fixed::setRawBits( int const raw ) {
	this->_fixedPointValue = raw;
}

float Fixed::toFloat( void ) const {
	return static_cast<float>(this->_fixedPointValue) / (1 << _fractionalBits);
}

int Fixed::toInt( void ) const {
	return this->_fixedPointValue >> _fractionalBits;
}

// -----------------------------------------------------------------------------------------------

// Comparison operators
bool Fixed::operator>( const Fixed& other ) const {
	return this->_fixedPointValue > other._fixedPointValue;
}

bool Fixed::operator<( const Fixed& other ) const {
	return this->_fixedPointValue < other._fixedPointValue;
}

bool Fixed::operator>=( const Fixed& other ) const {
	return this->_fixedPointValue >= other._fixedPointValue;
}

bool Fixed::operator<=( const Fixed& other ) const {
	return this->_fixedPointValue <= other._fixedPointValue;
}

bool Fixed::operator==( const Fixed& other ) const {
	return this->_fixedPointValue == other._fixedPointValue;
}

bool Fixed::operator!=( const Fixed& other ) const {
	return this->_fixedPointValue != other._fixedPointValue;
}

// -----------------------------------------------------------------------------------------------

// Arithmetic operators
Fixed Fixed::operator+( const Fixed& other ) const {
	Fixed result;
	result.setRawBits(this->_fixedPointValue + other._fixedPointValue);
	return result;
}

Fixed Fixed::operator-( const Fixed& other ) const {
	Fixed result;
	result.setRawBits(this->_fixedPointValue - other._fixedPointValue);
	return result;
}

Fixed Fixed::operator*( const Fixed& other ) const {
	Fixed result;
	result.setRawBits((this->_fixedPointValue * other._fixedPointValue) >> _fractionalBits);
	return result;
}

Fixed Fixed::operator/( const Fixed& other ) const {
	Fixed result;
	result.setRawBits((this->_fixedPointValue << _fractionalBits) / other._fixedPointValue);
	return result;
}

// Pre-increment
Fixed& Fixed::operator++( void ) {
	this->_fixedPointValue++;
	return *this;
}

// Post-increment
Fixed Fixed::operator++( int ) {
	Fixed temp(*this);
	this->_fixedPointValue++;
	return temp;
}

// Pre-decrement
Fixed& Fixed::operator--( void ) {
	this->_fixedPointValue--;
	return *this;
}

// Post-decrement
Fixed Fixed::operator--( int ) {
	Fixed temp(*this);
	this->_fixedPointValue--;
	return temp;
}

// -----------------------------------------------------------------------------------------------

// Static min/max functions
Fixed& Fixed::min( Fixed& a, Fixed& b ) {
	return (a < b) ? a : b;
}

const Fixed& Fixed::min( const Fixed& a, const Fixed& b ) {
	return (a < b) ? a : b;
}

Fixed& Fixed::max( Fixed& a, Fixed& b ) {
	return (a > b) ? a : b;
}

const Fixed& Fixed::max( const Fixed& a, const Fixed& b ) {
	return (a > b) ? a : b;
}

std::ostream& operator<<( std::ostream& out, const Fixed& fixed ) {
	out << fixed.toFloat();
	return out;
}
