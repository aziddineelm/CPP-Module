#include "Harl.hpp"

int main(int ac, char** av) {
	if (ac != 2) {
		std::cerr << "Usage: ./harlFilter <level>" << std::endl;
		return 1;
	}
	
	Harl harl;
	std::string level = av[1];
	int levelIndex = -1;
	
	std::string levels[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
	
	for (int i = 0; i < 4; i++) {
		if (levels[i] == level) {
			levelIndex = i;
			break;
		}
	}
	
	switch (levelIndex) {
		case 0:
			harl.complain("DEBUG");
			std::cout << std::endl;
		case 1:
			harl.complain("INFO");
			std::cout << std::endl;
		case 2:
			harl.complain("WARNING");
			std::cout << std::endl;
		case 3:
			harl.complain("ERROR");
			std::cout << std::endl;
			break;
		default:
			std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
	}
	
	return 0;
}