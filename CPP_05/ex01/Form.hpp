#pragma once

#include <iostream>
#include <string>
#include <exception>

class Bureaucrat;

class Form {
	private:
		const std::string _name;
		bool _isSigned;
		const int _gradeToSign;
		const int _gradeToExecute;


	public:

		Form();
		Form(std::string name, int gradeToSign, int gradeToExecute);
		Form(const Form& other);
		Form& operator=(const Form& other);
		~Form();

		// getters
		const std::string& getName() const;
		bool isSigned() const;
		int getGradeToSign() const;
		int getGradeToExecute() const;

		void	beSigned(const Bureaucrat& bureaucrat);

		// exceptions
		class GradeTooHighException : public std::exception {
			const char* what() const throw();
		};
		class GradeTooLowException : public std::exception {
			const char* what() const throw();
		};
};

std::ostream& operator<<(std::ostream& out, const Form& form);