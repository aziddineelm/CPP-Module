#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int main() {
	std::cout << "=== Testing Construction/Destruction Chaining ===" << std::endl;
	{
		std::cout << "\n--- Creating ScavTrap ST-001 ---" << std::endl;
		ScavTrap scav1("ST-001");
		
		std::cout << "\n--- Destroying ScavTrap ST-001 ---" << std::endl;
	}

	std::cout << "\n\n=== Testing ScavTrap Abilities ===" << std::endl;
	ScavTrap scav2("ST-002");
	
	std::cout << "\n--- ScavTrap Attack (20 damage) ---" << std::endl;
	scav2.attack("Enemy");
	
	std::cout << "\n--- Guard Gate Special Ability ---" << std::endl;
	scav2.guardGate();
	
	std::cout << "\n--- ScavTrap Repair ---" << std::endl;
	scav2.beRepaired(10);
	
	std::cout << "\n--- ScavTrap Take Damage ---" << std::endl;
	scav2.takeDamage(30);

	std::cout << "\n\n=== Testing ClapTrap vs ScavTrap ===" << std::endl;
	ClapTrap clap("CT-001");
	ScavTrap scav3("ST-003");
	
	std::cout << "\n--- ClapTrap Attack (0 damage) ---" << std::endl;
	clap.attack("Target");
	
	std::cout << "\n--- ScavTrap Attack (20 damage) ---" << std::endl;
	scav3.attack("Target");

	std::cout << "\n\n=== Testing Energy Depletion on ScavTrap ===" << std::endl;
	ScavTrap scav4("ST-004");
	std::cout << "Attacking 50 times to deplete energy..." << std::endl;
	for (int i = 0; i < 50; i++) {
		scav4.attack("Dummy");
	}
	std::cout << "\n--- Trying to attack with no energy ---" << std::endl;
	scav4.attack("Target");
	scav4.beRepaired(5);

	std::cout << "\n\n=== Testing Copy Constructor ===" << std::endl;
	ScavTrap scav5("ST-005");
	ScavTrap scav6(scav5);
	
	std::cout << "\n=== Testing Copy Assignment ===" << std::endl;
	ScavTrap scav7("ST-007");
	scav7 = scav5;

	std::cout << "\n\n=== Destroying All Objects ===" << std::endl;
	return 0;
}
