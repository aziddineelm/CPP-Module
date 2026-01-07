#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main() {
	std::cout << "=== Test 1: FragTrap Construction ===" << std::endl;
	FragTrap frag1("Fraggy");

	std::cout << "\n=== Test 2: FragTrap Attack (30 damage) ===" << std::endl;
	frag1.attack("enemy");

	std::cout << "\n=== Test 3: High Five Special Ability ===" << std::endl;
	frag1.highFivesGuys();

	std::cout << "\n=== Test 4: Take Damage and Repair ===" << std::endl;
	frag1.takeDamage(60);
	frag1.beRepaired(30);

	std::cout << "\n=== Test 5: All Three Types ===" << std::endl;
	ClapTrap clap("Clappy");
	ScavTrap scav("Scavvy");
	FragTrap frag2("Fraggy2");
	
	clap.attack("target");
	scav.attack("target");
	frag2.attack("target");
	
	scav.guardGate();
	frag2.highFivesGuys();

	std::cout << "\n=== Test 6: Energy Depletion ===" << std::endl;
	FragTrap frag3("Tired");
	for (int i = 0; i < 100; i++)
		frag3.attack("dummy");
	frag3.attack("should fail");
	frag3.beRepaired(1);

	std::cout << "\n=== Test 7: Death ===" << std::endl;
	FragTrap frag4("Mortal");
	frag4.takeDamage(100);
	frag4.attack("should fail");
	frag4.highFivesGuys();

	std::cout << "\n=== Test 8: Copy Constructor ===" << std::endl;
	FragTrap frag5("Original");
	FragTrap frag6(frag5);
	frag6.highFivesGuys();

	std::cout << "\n=== Test 9: Assignment Operator ===" << std::endl;
	FragTrap frag7("First");
	FragTrap frag8("Second");
	frag8 = frag7;

	std::cout << "\n=== Destruction ===" << std::endl;
	return 0;
}
