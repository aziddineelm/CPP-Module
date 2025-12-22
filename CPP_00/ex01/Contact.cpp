#include "Contact.hpp"
#include "PhoneBook.hpp"

Contact::Contact() {}
Contact::~Contact() {}

bool isValidNumber(const std::string &phone) {
    for (size_t i = 0; i < phone.length(); i++) {
        char c = phone[i];
        if (!std::isdigit(c) && c != '-' && c != ' ' && !(c == '+' && i == 0))
            return false;
    }
    return true;
}

bool hasNonPrintable(const std::string &str) {
    for (size_t i = 0; i < str.length(); i++) {
        if (!std::isprint(static_cast<unsigned char>(str[i]))) {
			std::cout << RED << "None Printable Detected!!" << RESET << std::endl;
            return true;
		}
    }
    return false;
}

std::string getInput(const std::string &prompt) {
	std::string input;
	bool firstTime = true;
	while (input.empty() || hasNonPrintable(input)) {
		if (firstTime)
            std::cout << "Enter " << prompt;
        else
            std::cout << "Please enter " << prompt;
        firstTime = false;
		std::getline(std::cin, input);
		if (std::cin.eof())
			exit (0);
	}
	return input;
}

void Contact::setInfo() {
	std::cout << std::endl;

	firstName = getInput("First Name: ");

	lastName = getInput("Last Name: ");

	nickName = getInput("Nick Name: ");

	phoneNumber = getInput("Phone number: ");

	while (!isValidNumber(phoneNumber))
		phoneNumber = getInput("a valid phone number: ");

	darkSecret = getInput("Dark secret: ");

}

std::string Contact::getFirstName() const {
    return firstName;
}

std::string Contact::getLastName() const {
    return lastName;
}

std::string Contact::getNickName() const {
    return nickName;
}

std::string Contact::getPhoneNumber() const {
    return phoneNumber;
}

std::string Contact::getDarkSecret() const {
    return darkSecret;
}