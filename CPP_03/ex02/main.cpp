#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main() {
	std::cout << "=== Testing Construction/Destruction Chaining ===" << std::endl;
	{
		std::cout << "\n--- Creating FragTrap FT-001 ---" << std::endl;
		FragTrap frag1("FT-001");
		
		std::cout << "\n--- Destroying FragTrap FT-001 ---" << std::endl;
	}

	std::cout << "\n\n=== Testing FragTrap Abilities ===" << std::endl;
	FragTrap frag2("FT-002");
	
	std::cout << "\n--- FragTrap Attack (30 damage) ---" << std::endl;
	frag2.attack("Enemy");
	
	std::cout << "\n--- High Five Special Ability ---" << std::endl;
	frag2.highFivesGuys();
	
	std::cout << "\n--- FragTrap Repair ---" << std::endl;
	frag2.beRepaired(25);
	
	std::cout << "\n--- FragTrap Take Damage ---" << std::endl;
	frag2.takeDamage(50);

	std::cout << "\n\n=== Testing ClapTrap vs ScavTrap vs FragTrap ===" << std::endl;
	ClapTrap clap("CT-001");
	ScavTrap scav("ST-001");
	FragTrap frag3("FT-003");
	
	std::cout << "\n--- ClapTrap Attack (0 damage, 10 energy) ---" << std::endl;
	clap.attack("Target");
	
	std::cout << "\n--- ScavTrap Attack (20 damage, 50 energy) ---" << std::endl;
	scav.attack("Target");
	
	std::cout << "\n--- FragTrap Attack (30 damage, 100 energy) ---" << std::endl;
	frag3.attack("Target");

	std::cout << "\n--- ScavTrap Special Ability ---" << std::endl;
	scav.guardGate();
	
	std::cout << "\n--- FragTrap Special Ability ---" << std::endl;
	frag3.highFivesGuys();

	std::cout << "\n\n=== Testing Energy Depletion on FragTrap ===" << std::endl;
	FragTrap frag4("FT-004");
	std::cout << "Attacking 100 times to deplete energy..." << std::endl;
	for (int i = 0; i < 100; i++) {
		frag4.attack("Dummy");
	}
	std::cout << "\n--- Trying to attack with no energy ---" << std::endl;
	frag4.attack("Target");
	frag4.beRepaired(5);

	std::cout << "\n\n=== Testing Copy Constructor ===" << std::endl;
	FragTrap frag5("FT-005");
	FragTrap frag6(frag5);
	frag6.highFivesGuys();
	
	std::cout << "\n=== Testing Copy Assignment ===" << std::endl;
	FragTrap frag7("FT-007");
	frag7 = frag5;
	frag7.highFivesGuys();

	std::cout << "\n\n=== Testing Damage Until Death ===" << std::endl;
	FragTrap frag8("FT-008");
	frag8.takeDamage(50);
	frag8.takeDamage(60);
	frag8.attack("Enemy");
	frag8.beRepaired(10);

	std::cout << "\n\n=== Destroying All Objects ===" << std::endl;
	return 0;
}
