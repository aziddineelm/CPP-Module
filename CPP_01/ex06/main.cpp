#include "Harl.hpp"

int main(int ac, char** av) {
	if (ac != 2) {
		std::cerr << "		***		Error: You must add <level> 	***" << std::endl;
		std::cout << "		*** 	[\"WARNING\", \"DEBUG\", \"ERROR\", \"INFO\"]	 ***" << std::endl;
		return 1;
	}
	
	Harl harl;
	std::string level = av[1];
	int levelIndex;
	
	std::string levels[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
	
	for (int i = 0; i < 4; i++) {
		if (levels[i] == level) {
			levelIndex = i;
			break;
		} else 
			levelIndex = -1;
	}
	
	switch (levelIndex) {
		case 0:
			harl.complain("DEBUG");
			std::cout << std::endl;
			// fallthrough
		case 1:
			harl.complain("INFO");
			std::cout << std::endl;
			// fallthrough
		case 2:
			harl.complain("WARNING");
			std::cout << std::endl;
			// fallthrough
		case 3:
			harl.complain("ERROR");
			std::cout << std::endl;
			break;
		default:
			std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
	}
	
	return 0;
}