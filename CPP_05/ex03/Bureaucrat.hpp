#pragma once

#include <string>
#include <iostream>
#include <exception>

class AForm;

class Bureaucrat {
	private:
		const std::string _name;
		int _grade;
	public:
		Bureaucrat();
		Bureaucrat(std::string name, int grade);
		Bureaucrat (const Bureaucrat& other);
		Bureaucrat& operator=(const Bureaucrat& other);
		~Bureaucrat();
		
		// Getters
		const std::string& getName() const;
		int getGrade() const;
		void incrementGrade();
		void decrementGrade();

		void signForm(AForm& form);
		void executeForm(AForm const & form);
		class GradeTooHighException : public std::exception {
			public:
				const char* what() const throw();	
		};
		class GradeTooLowException : public std::exception {
			public:
				const char* what() const throw();
		};
};

std::ostream& operator<<( std::ostream& out, const Bureaucrat& fixed );