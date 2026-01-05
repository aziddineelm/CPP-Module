#include "ClapTrap.hpp"

int main() {
	std::cout << "=== Creating ClapTraps ===" << std::endl;
	ClapTrap clap1("CT-001");
	ClapTrap clap2("CT-002");

	std::cout << "\n=== Testing Attacks ===" << std::endl;
	clap1.attack("Enemy");
	clap1.attack("Enemy");
	clap1.attack("Enemy");

	std::cout << "\n=== Testing Damage ===" << std::endl;
	clap2.takeDamage(5);
	clap2.takeDamage(3);

	std::cout << "\n=== Testing Repair ===" << std::endl;
	clap2.beRepaired(429496729);
	clap2.beRepaired(12);

	std::cout << "\n=== Testing Energy Depletion ===" << std::endl;
	for (int i = 0; i < 10; i++) {
		clap1.attack("Target");
	}
	clap1.attack("Target");

	std::cout << "\n=== Testing Death ===" << std::endl;
	clap2.takeDamage(20);
	clap2.attack("Someone");
	clap2.beRepaired(5);

	std::cout << "\n=== Destroying ClapTraps ===" << std::endl;
	return 0;
}
