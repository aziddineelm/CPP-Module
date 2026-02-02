#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

int main() {
	std::cout << "=== Testing Intern Class ===" << std::endl;
	
	Intern someRandomIntern;
	AForm* form1;
	AForm* form2;
	AForm* form3;
	AForm* form4;

	std::cout << "\n--- Creating robotomy request form ---" << std::endl;
	form1 = someRandomIntern.makeForm("robotomy request", "Bender");
	
	std::cout << "\n--- Creating presidential pardon form ---" << std::endl;
	form2 = someRandomIntern.makeForm("presidential pardon", "Arthur Dent");
	
	std::cout << "\n--- Creating shrubbery creation form ---" << std::endl;
	form3 = someRandomIntern.makeForm("shrubbery creation", "home");
	
	std::cout << "\n--- Attempting to create unknown form ---" << std::endl;
	form4 = someRandomIntern.makeForm("unknown form", "target");
	
	if (form4) {
		delete form4;
	}

	std::cout << "\n--- Testing created forms ---" << std::endl;
	if (form1) {
		std::cout << *form1 << std::endl;
		try {
			Bureaucrat bob("Bob", 1);
			bob.signForm(*form1);
			bob.executeForm(*form1);
		}
		catch (std::exception& e) {
			std::cerr << "Exception: " << e.what() << std::endl;
		}
	}

	if (form2) {
		std::cout << *form2 << std::endl;
		try {
			Bureaucrat alice("Alice", 1);
			alice.signForm(*form2);
			alice.executeForm(*form2);
		}
		catch (std::exception& e) {
			std::cerr << "Exception: " << e.what() << std::endl;
		}
	}

	if (form3) {
		std::cout << *form3 << std::endl;
		try {
			Bureaucrat charlie("Charlie", 1);
			charlie.signForm(*form3);
			charlie.executeForm(*form3);
		}
		catch (std::exception& e) {
			std::cerr << "Exception: " << e.what() << std::endl;
		}
	}

	// Clean up
	delete form1;
	delete form2;
	delete form3;
	// form4 is NULL, safe to delete

	std::cout << "\n=== Additional Tests ===" << std::endl;
	
	std::cout << "\n--- Test with multiple interns ---" << std::endl;
	{
		Intern intern1;
		Intern intern2;
		
		AForm* f1 = intern1.makeForm("robotomy request", "Target1");
		AForm* f2 = intern2.makeForm("presidential pardon", "Target2");
		
		delete f1;
		delete f2;
	}

	std::cout << "\n=== All Tests Complete ===" << std::endl;
	return 0;
}