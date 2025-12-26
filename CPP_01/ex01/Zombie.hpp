#pragma once

#include <string>
#include <iostream>

class Zombie {
	private:
		std::string _name;	
	public:
		Zombie();
		~Zombie();
		void announce( void );
		void setName ( const std::string& name );
};

Zombie* zombieHorde( int N, std::string name );