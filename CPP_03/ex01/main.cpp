#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int main() {
	std::cout << "=== Test 1: ScavTrap Construction ===" << std::endl;
	ScavTrap scav1("Guardian");

	std::cout << "\n=== Test 2: ScavTrap Attack (20 damage) ===" << std::endl;
	scav1.attack("intruder");

	std::cout << "\n=== Test 3: Guard Gate Special Ability ===" << std::endl;
	scav1.guardGate();

	std::cout << "\n=== Test 4: Take Damage and Repair ===" << std::endl;
	scav1.takeDamage(40);
	scav1.beRepaired(20);

	std::cout << "\n=== Test 5: ClapTrap vs ScavTrap ===" << std::endl;
	ClapTrap clap("Clappy");
	ScavTrap scav2("Scavvy");
	clap.attack("target");
	scav2.attack("target");

	std::cout << "\n=== Test 6: Energy Depletion ===" << std::endl;
	ScavTrap scav3("Exhausted");
	for (int i = 0; i < 50; i++)
		scav3.attack("dummy");
	scav3.attack("should fail");
	scav3.beRepaired(1);

	std::cout << "\n=== Test 7: Death ===" << std::endl;
	ScavTrap scav4("Mortal");
	scav4.takeDamage(100);
	scav4.attack("should fail");
	scav4.guardGate();

	std::cout << "\n=== Test 8: Copy Constructor ===" << std::endl;
	ScavTrap scav5("Original");
	ScavTrap scav6(scav5);

	std::cout << "\n=== Test 9: Assignment Operator ===" << std::endl;
	ScavTrap scav7("First");
	ScavTrap scav8("Second");
	scav8 = scav7;

	std::cout << "\n=== Destruction ===" << std::endl;
	return 0;
}
