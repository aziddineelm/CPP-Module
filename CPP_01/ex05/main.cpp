#include "Harl.hpp"

#define BLUE    "\033[1;34m"
#define RESET   "\033[0m"


int main() {
	Harl harl;
	std::string report;

	std::cout << BLUE << "		***			Hello There!!		 ***" << RESET << std::endl;
	std::cout << BLUE << "		***			Your Report:		 ***" << RESET << std::endl;
	std::cout << BLUE << "		*** 	[\"WARNING\", \"DEBUG\", \"ERROR\", \"INFO\"]	 ***" << RESET << std::endl;
	std::cout << std::endl;
	std::cout << "Plese Entre Your Report: ";
	std::getline(std::cin, report);

	harl.complain(report);

	return 0;
}