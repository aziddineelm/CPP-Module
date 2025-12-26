#include "Zombie.hpp"

Zombie::Zombie() {}
Zombie::~Zombie() {
	std::cout << _name << ": Destroyed!" << std::endl;
}

void Zombie::announce( void ) {
	std::cout << _name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

void Zombie::setName ( const std::string& name ) {
	this->_name = name;
}