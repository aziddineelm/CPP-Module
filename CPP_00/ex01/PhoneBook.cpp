#include "PhoneBook.hpp"
#include "Contact.hpp"

PhoneBook::PhoneBook() {
	index = 0;
	count = 0;
}

PhoneBook::~PhoneBook() {}

std::string formatColumn(const std::string &str) {
    if (str.length() > 10)
        return str.substr(0, 9) + ".";
    return str;
}

void PhoneBook::addContact() {
    contact[index].setInfo();
    index = (index + 1) % 8;
    if (count < 8)
        count++;
}

void printHeader() {
	std::cout << "---------------------------------------------" << std::endl;
	std::string prompt[4] = {"index", "first name", "last name", "nickname"};
	for (int i = 0; i < 4 ; i++) {
		std::cout << "|";
		std::cout << std::right << std::setw(10);
		std::cout << prompt[i];
	}
	std::cout << "|" << std::endl;
	std::cout << "---------------------------------------------" << std::endl;
}

void PhoneBook::searchContact() {
	if (count == 0) {
        std::cout << RED << "PhoneBook is empty!" << RESET << std::endl;
        return;
    }
	printHeader();
	for (int i = 0; i < count; i++) {
        std::cout << "|" << std::right << std::setw(10) << i;
        std::cout << "|" << std::right << std::setw(10) << formatColumn(contact[i].getFirstName());
        std::cout << "|" << std::right << std::setw(10) << formatColumn(contact[i].getLastName());
        std::cout << "|" << std::right << std::setw(10) << formatColumn(contact[i].getNickName());
        std::cout << "|" << std::endl;
    }
	std::cout << "---------------------------------------------" << std::endl;

	std::cout << BLUE << "Enter index to view details: " << RESET;
    std::string input;
    std::getline(std::cin, input);
    if (input.length() != 1 || input[0] < '0' || input[0] > '7' || (input[0] - '0') >= count) {
        std::cout << RED << "Invalid index!" << RESET << std::endl;
        return;
    }
    int idx = input[0] - '0';
	std::cout << std::endl;
    std::cout << "First Name: " << contact[idx].getFirstName() << std::endl;
    std::cout << "Last Name: " << contact[idx].getLastName() << std::endl;
    std::cout << "Nickname: " << contact[idx].getNickName() << std::endl;
    std::cout << "Phone Number: " << contact[idx].getPhoneNumber() << std::endl;
    std::cout << "Dark Secret: " << contact[idx].getDarkSecret() << std::endl;
}
