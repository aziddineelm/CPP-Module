#include "ClapTrap.hpp"

int main() {
	std::cout << "=== Test 1: Basic Construction ===" << std::endl;
	ClapTrap clap1("Bob");
	ClapTrap clap2("Alice");

	std::cout << "\n=== Test 2: Attack ===" << std::endl;
	clap1.attack("target");
	clap1.attack("enemy");

	std::cout << "\n=== Test 3: Take Damage ===" << std::endl;
	clap2.takeDamage(5);
	clap2.takeDamage(3);

	std::cout << "\n=== Test 4: Repair ===" << std::endl;
	clap2.beRepaired(4);

	std::cout << "\n=== Test 5: Energy Depletion ===" << std::endl;
	ClapTrap clap3("Charlie");
	for (int i = 0; i < 10; i++)
		clap3.attack("dummy");
	clap3.attack("should fail");
	clap3.beRepaired(1);

	std::cout << "\n=== Test 6: Death ===" << std::endl;
	ClapTrap clap4("David");
	clap4.takeDamage(10);
	clap4.attack("should fail");
	clap4.beRepaired(5);

	std::cout << "\n=== Test 7: Copy Constructor ===" << std::endl;
	ClapTrap clap5("Original");
	ClapTrap clap6(clap5);

	std::cout << "\n=== Test 8: Assignment Operator ===" << std::endl;
	ClapTrap clap7("First");
	ClapTrap clap8("Second");
	clap8 = clap7;

	std::cout << "\n=== Destruction ===" << std::endl;
	return 0;
}
