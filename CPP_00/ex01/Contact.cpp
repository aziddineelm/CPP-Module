#include "Contact.hpp"

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

std::string getInput(const std::string &prompt, bool isRetry = false) {
	std::string input;
	bool firstTime = true;
	while (input.empty()) {
		if (firstTime && !isRetry)
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
		phoneNumber = getInput(" a valid phone number: ", true);

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