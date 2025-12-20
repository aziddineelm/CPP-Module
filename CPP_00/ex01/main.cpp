#include "Contact.hpp"
#include "PhoneBook.hpp"

int main() {
	PhoneBook phonebook;
	std::cout << GREEN << "		*** Welcome to your PhoneBook app. ***" << std::endl;
	std::cout << BLUE << "		*** [ Options ] |  ADD  | SEARCH |  EXIT  | ***" << std::endl;
	std::string input;
	while (true) {
		std::cout << std::endl;
		std::cout << BLUE << "Please insert your option: " << RESET;
		if (!std::getline(std::cin, input)) {
    		std::cout << std::endl;
			break;
		}
		if (input == "ADD") {
			phonebook.addContact();
		} else if (input == "SEARCH") {
			phonebook.searchContact();
		} else if (input == "EXIT") {
			break;
		} else {
			std::cout << RED << "Error:" << RESET << " Please enter a valid option!!" << std::endl;
			std::cout << YELLOW << "Options: |  ADD  | SEARCH |  EXIT  |" << RESET;
		}
	}
	std::cout << GREEN << "\n	*** GoodBye 👋 ***" << std::endl;
	return 0;
}