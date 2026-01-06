#include "ClapTrap.hpp"

ClapTrap::ClapTrap() { _name = "aaaa" ;
	_HitPoint = 10; _EnergyPoint = 10; _AttackDamage = 0;
	std::cout << "ClapTrap Default constructor called" << std::endl;
}

ClapTrap::ClapTrap( std::string name) : 
	_name(name), _HitPoint(10), _EnergyPoint(10), _AttackDamage(0)
{
	std::cout << "ClapTrap " << _name << " constructed" << std::endl;
}

ClapTrap::ClapTrap( const ClapTrap& other ) {
	std::cout << "ClapTrap Copy constructor called" << std::endl;
	_name = other._name;
	_HitPoint = other._HitPoint;
	_EnergyPoint = other._EnergyPoint;
	_AttackDamage = other._AttackDamage;
}

ClapTrap& ClapTrap::operator=(const ClapTrap& other) {
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &other) {
		_name = other._name;
		_HitPoint = other._HitPoint;
		_EnergyPoint = other._EnergyPoint;
		_AttackDamage = other._AttackDamage; 
	}
	return *this;
}

ClapTrap::~ClapTrap() {
	std::cout << "ClapTrap " << _name << " destroyed" << std::endl;
}

void ClapTrap::attack(const std::string& target) {
	if (_HitPoint == 0) {
		std::cout << "ClapTrap " << _name << " is dead and cannot attack!" << std::endl;
		return;
	}
	if (_EnergyPoint == 0) {
		std::cout << "ClapTrap " << _name << " has no energy points left!" << std::endl;
		return;
	}
	_EnergyPoint--;
	std::cout << "ClapTrap " << _name << " attacks " << target 
		<< ", causing " << _AttackDamage << " points of damage!" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount) {
	if (_HitPoint == 0) {
		std::cout << "ClapTrap " << _name << " is already dead!" << std::endl;
		return;
	}
	if (amount >= _HitPoint) {
		_HitPoint = 0;
		std::cout << "ClapTrap " << _name << " takes " << amount 
			<< " points of damage and dies!" << std::endl;
	} else {
		_HitPoint -= amount;
		std::cout << "ClapTrap " << _name << " takes " << amount 
			<< " points of damage! (" << _HitPoint << " HP left)" << std::endl;
	}
}

void ClapTrap::beRepaired(unsigned int amount) {
	if (_HitPoint == 0) {
		std::cout << "ClapTrap " << _name << " is dead and cannot repair itself!" << std::endl;
		return;
	}
	if (_EnergyPoint == 0) {
		std::cout << "ClapTrap " << _name << " has no energy points left to repair!" << std::endl;
		return;
	}
	_EnergyPoint--;
	_HitPoint += amount;
	std::cout << "ClapTrap " << _name << " repairs itself for " << amount 
		<< " hit points! (" << _HitPoint << " HP total)" << std::endl;
}
