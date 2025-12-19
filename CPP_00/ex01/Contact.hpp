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
		
};