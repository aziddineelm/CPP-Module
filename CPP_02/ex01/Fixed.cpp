#include "Fixed.hpp"

Fixed::Fixed() : _fixedPointValue(0) {
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed( const int intVal ) {
	std::cout << "Int constructor called" << std::endl;
	this->_fixedPointValue = intVal << _fractionalBits;
}

Fixed::Fixed( const float floatVal ) {
	std::cout << "Float constructor called" << std::endl;
	this->_fixedPointValue = (roundf(floatVal * (1 << _fractionalBits)));
}

Fixed::Fixed( const Fixed& other ) {
	std::cout << "Copy constructor called" << std::endl;
	this->_fixedPointValue = other.getRawBits();
}

Fixed& Fixed::operator=( const Fixed& other ) {
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &other)
		this->_fixedPointValue = other.getRawBits();
	return *this;
}

Fixed::~Fixed() {
	std::cout << "Destructor called" << std::endl;
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

std::ostream& operator<<( std::ostream& out, const Fixed& fixed ) {
	out << fixed.toFloat();
	return out;
}
