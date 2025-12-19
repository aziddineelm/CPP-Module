#include "Contact.hpp"

bool isValidNumber(const std::string &phone) {
    for (size_t i = 0; i < phone.length(); i++) {
        char c = phone[i];
        if (!std::isdigit(c) && c != '-' && c != ' ' && !(c == '+' && i == 0)) {
    		std::cout << "Invalid phone number. Try again: ";
            return false;
		}
    }
    return true;
}

std::string getInput(const std::string &prompt) {
	std::string input;
	int firstTime = true;
	while (input.empty()) {
		if (firstTime)
            std::cout << "Enter " << prompt;
        else
            std::cout << "Please enter " << prompt;
        firstTime = false;
		std::getline(std::cin, input);
		if (std::cin.eof())
			break;
	}
	return input;
}

void Contact::setInfo() {
	
	firstName = getInput("First Name: ");

	lastName = getInput("Last Name: ");

	nickName = getInput("Nick Name: ");

	phoneNumber = getInput("Phone number: ");

	while (!isValidNumber(phoneNumber))
		phoneNumber = getInput("Phone number: ");

	darkSecret = getInput("Dark secret: ");

}