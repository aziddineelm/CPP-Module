#pragma once

#include <string>
#include "AForm.hpp"

class Intern {
	public:
		Intern();
		Intern(const Intern& other);
		Intern& operator=(const Intern& other);
		~Intern();

		AForm* makeForm(std::string formName, std::string target);

	private:
		// Helper functions to create each form type
		AForm* createShrubberyCreationForm(std::string target);
		AForm* createRobotomyRequestForm(std::string target);
		AForm* createPresidentialPardonForm(std::string target);
};