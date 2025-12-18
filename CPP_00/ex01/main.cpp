#include "Contact.hpp"
#include "PhoneBook.hpp"

int main() {
	std::cout << GREEN << "\n		*** Welcome to your PhoneBook app. ***\n";
	std::cout << BLUE << "\n		*** Options: |  ADD  | SEARCH |  EXIT  | ***\n";
	std::string input;
	while (true) {
		std::cout << BLUE << "Please insert your option: " << RESET;
		if (!std::getline(std::cin, input)) {
			std::cout << std::endl;
			break;
		}
		if (input == "ADD") {

		} else if (input == "SEARCH") {

		} else if (input == "EXIT") {
			break;
		} else {
			std::cout << RED << "Error: " << RESET << "Please entre a valid option!!\n";
			std::cout << BLUE << "Options: |  ADD  | SEARCH |  EXIT  |\n" << RESET;
		}
	}
	std::cout << GREEN << "\n	*** GoodBye 👋 ***\n";
	return 0;
}