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
};

std::ostream& operator<<( std::ostream& out, const Fixed& fixed );