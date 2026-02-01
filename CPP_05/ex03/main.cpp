#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main() {
	std::cout << "=== Testing ShrubberyCreationForm ===" << std::endl;
	try {
		Bureaucrat bob("Bob", 140);
		ShrubberyCreationForm shrub("home");
		
		std::cout << bob << std::endl;
		std::cout << shrub << std::endl;
		
		bob.signForm(shrub);
		bob.executeForm(shrub);
	}
	catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Testing RobotomyRequestForm ===" << std::endl;
	try {
		Bureaucrat alice("Alice", 40);
		RobotomyRequestForm robot("Bender");
		
		std::cout << alice << std::endl;
		std::cout << robot << std::endl;
		
		alice.signForm(robot);
		alice.executeForm(robot);
	}
	catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Testing PresidentialPardonForm ===" << std::endl;
	try {
		Bureaucrat president("President", 1);
		PresidentialPardonForm pardon("Arthur Dent");
		
		std::cout << president << std::endl;
		std::cout << pardon << std::endl;
		
		president.signForm(pardon);
		president.executeForm(pardon);
	}
	catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Testing Form Not Signed Exception ===" << std::endl;
	try {
		Bureaucrat charlie("Charlie", 1);
		ShrubberyCreationForm form("garden");
		
		std::cout << charlie << std::endl;
		// Try to execute without signing
		charlie.executeForm(form);
	}
	catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Testing Grade Too Low to Sign ===" << std::endl;
	try {
		Bureaucrat intern("Intern", 150);
		PresidentialPardonForm pardon("Ford Prefect");
		
		std::cout << intern << std::endl;
		std::cout << pardon << std::endl;
		
		intern.signForm(pardon);
	}
	catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Testing Grade Too Low to Execute ===" << std::endl;
	try {
		Bureaucrat boss("Boss", 5);
		Bureaucrat worker("Worker", 50);
		PresidentialPardonForm pardon("Zaphod");
		
		std::cout << boss << std::endl;
		std::cout << worker << std::endl;
		std::cout << pardon << std::endl;
		
		boss.signForm(pardon);
		// Worker tries to execute but doesn't have high enough grade
		worker.executeForm(pardon);
	}
	catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== All Tests Complete ===" << std::endl;
	return 0;
}