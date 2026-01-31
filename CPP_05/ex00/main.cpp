#include "Bureaucrat.hpp"

int main() {
	// Test valid bureaucrat
	try {
		Bureaucrat bob("Bob", 50);
		std::cout << bob << std::endl;
		
		bob.incrementGrade();
		std::cout << "After increment: " << bob << std::endl;
			
		bob.decrementGrade();
		std::cout << "After decrement: " << bob << std::endl;
	}
	catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	// Test grade too high (grade < 1)
	std::cout << "\n--- Testing GradeTooHighException ---" << std::endl;
	try {
		Bureaucrat highGrade("HighBob", 0);
	}
	catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	// Test grade too low (grade > 150)
	std::cout << "\n--- Testing GradeTooLowException ---" << std::endl;
	try {
		Bureaucrat lowGrade("LowBob", 151);
	}
	catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	// Test increment at max grade (grade 1)
	std::cout << "\n--- Testing increment at grade 1 ---" << std::endl;
	try {
		Bureaucrat maxGrade("MaxBob", 1);
		std::cout << maxGrade << std::endl;
		maxGrade.incrementGrade();
	}
	catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	// Test decrement at min grade (grade 150)
	std::cout << "\n--- Testing decrement at grade 150 ---" << std::endl;
	try {
		Bureaucrat minGrade("MinBob", 150);
		std::cout << minGrade << std::endl;
		minGrade.decrementGrade();
	}
	catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	return 0;
}