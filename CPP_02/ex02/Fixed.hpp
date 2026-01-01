#pragma once

#include <iostream>
#include <cmath>

class Fixed {
	private:
		int	_fixedPointValue;
		static const int _fractionalBits = 8; 
	public:
		Fixed();
		Fixed( const int intVal );
		Fixed( const float floatVal );
		Fixed( const Fixed& other );
		Fixed& operator=( const Fixed& other );
		~Fixed();

		int		getRawBits( void ) const;
		void	setRawBits( int const raw );
		float	toFloat( void ) const;
		int		toInt( void ) const;

		// Comparison operators
		bool operator>( const Fixed& other ) const;
		bool operator<( const Fixed& other ) const;
		bool operator>=( const Fixed& other ) const;
		bool operator<=( const Fixed& other ) const;
		bool operator==( const Fixed& other ) const;
		bool operator!=( const Fixed& other ) const;

		// Arithmetic operators
		Fixed operator+( const Fixed& other ) const;
		Fixed operator-( const Fixed& other ) const;
		Fixed operator*( const Fixed& other ) const;
		Fixed operator/( const Fixed& other ) const;

		// Increment/Decrement operators
		Fixed& operator++( void );		// Pre-increment
		Fixed operator++( int );		// Post-increment
		Fixed& operator--( void );		// Pre-decrement
		Fixed operator--( int );		// Post-decrement

		// Static min/max functions
		static Fixed& min( Fixed& a, Fixed& b );
		static const Fixed& min( const Fixed& a, const Fixed& b );
		static Fixed& max( Fixed& a, Fixed& b );
		static const Fixed& max( const Fixed& a, const Fixed& b );
};

std::ostream& operator<<( std::ostream& out, const Fixed& fixed );
