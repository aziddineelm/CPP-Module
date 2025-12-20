#pragma once

#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>


class Contact {
	private:
		std::string firstName;
		std::string lastName;
		std::string nickName;
		std::string phoneNumber;
		std::string darkSecret;
	public:
		void setInfo();
		Contact();
		~Contact();
		std::string getFirstName() const;
        std::string getLastName() const;
        std::string getNickName() const;
        std::string getPhoneNumber() const;
        std::string getDarkSecret() const;
};