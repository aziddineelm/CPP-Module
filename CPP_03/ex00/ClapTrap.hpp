#pragma once

#include <string>
#include <iostream>
#include <climits>

class ClapTrap {
	private:
		std::string _name;
		unsigned int _HitPoint;
		unsigned int _EnergyPoint;
		unsigned int _AttackDamage;
	public:
		ClapTrap ();
		ClapTrap( std::string name);
		ClapTrap(const ClapTrap& other);
		ClapTrap& operator= (const ClapTrap& other);
		~ClapTrap();
		void attack(const std::string& target);
		void takeDamage(unsigned int amount);
		void beRepaired(unsigned int amount);
};
