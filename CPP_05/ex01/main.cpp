#include "Bureaucrat.hpp"
#include "Form.hpp"

int main() {
	std::cout << "=== Testing Form Creation ===" << std::endl;
	
	// Test valid form
	try {
		Form tax("Tax Form", 50, 25);
		std::cout << tax << std::endl;
	}
	catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	// Test form with grade too high
	std::cout << "\n--- Testing Form GradeTooHighException ---" << std::endl;
	try {
		Form invalid("Invalid Form", 0, 50);
	}
	catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	// Test form with grade too low
	std::cout << "\n--- Testing Form GradeTooLowException ---" << std::endl;
	try {
		Form invalid("Invalid Form", 50, 151);
	}
	catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Testing Form Signing ===" << std::endl;
	
	// Test successful signing
	std::cout << "\n--- Bureaucrat can sign form ---" << std::endl;
	try {
		Bureaucrat bob("Bob", 40);
		Form permit("Building Permit", 50, 30);
		
		std::cout << permit << std::endl;
		std::cout << bob << std::endl;
		
		bob.signForm(permit);
		std::cout << permit << std::endl;
	}
	catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	// Test failed signing (grade too low)
	std::cout << "\n--- Bureaucrat cannot sign form (grade too low) ---" << std::endl;
	try {
		Bureaucrat intern("Intern", 100);
		Form contract("Contract", 50, 25);
		
		std::cout << contract << std::endl;
		std::cout << intern << std::endl;
		
		intern.signForm(contract);
		std::cout << contract << std::endl;
	}
	catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	// Test signing already signed form
	std::cout << "\n--- Signing already signed form ---" << std::endl;
	try {
		Bureaucrat alice("Alice", 10);
		Bureaucrat charlie("Charlie", 20);
		Form report("Report", 30, 15);
		
		alice.signForm(report);
		charlie.signForm(report);
	}
	catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	return 0;
}