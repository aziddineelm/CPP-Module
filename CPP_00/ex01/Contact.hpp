#pragma once

#include <string>
#include 

class Contact {
	private:
		std::string firstName;
		std::string lastName;
		std::string nickName;
		std::string phoneNumber;
		std::string darkSecret;
	public:
		void getInfo();
		
};