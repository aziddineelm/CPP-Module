#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>

Intern::Intern() {
	// std::cout << "Intern default constructor called" << std::endl;
}

Intern::Intern(const Intern& other) {
	// std::cout << "Intern copy constructor called" << std::endl;
	(void)other;
}

Intern& Intern::operator=(const Intern& other) {
	// std::cout << "Intern assignment operator called" << std::endl;
	(void)other;
	return *this;
}

Intern::~Intern() {
	// std::cout << "Intern destructor called" << std::endl;
}

AForm* Intern::createShrubberyCreationForm(std::string target) {
	return new ShrubberyCreationForm(target);
}

AForm* Intern::createRobotomyRequestForm(std::string target) {
	return new RobotomyRequestForm(target);
}

AForm* Intern::createPresidentialPardonForm(std::string target) {
	return new PresidentialPardonForm(target);
}

AForm* Intern::makeForm(std::string formName, std::string target) {
	// Array of form names
	std::string formNames[3] = {
		"shrubbery creation",
		"robotomy request",
		"presidential pardon"
	};

	// Array of function pointers to form creation methods
	AForm* (Intern::*formCreators[3])(std::string) = {
		&Intern::createShrubberyCreationForm,
		&Intern::createRobotomyRequestForm,
		&Intern::createPresidentialPardonForm
	};

	// Search for the form name
	for (int i = 0; i < 3; i++) {
		if (formName == formNames[i]) {
			std::cout << "Intern creates " << formName << std::endl;
			return (this->*formCreators[i])(target);
		}
	}

	// Form not found
	std::cerr << "Error: Form name \"" << formName << "\" does not exist." << std::endl;
	return NULL;
}
