#pragma once

#include <iostream>
#include <string>
#include <exception>

class Bureaucrat;

class AForm {
	private:
		const std::string _name;
		bool _isSigned;
		const int _gradeToSign;
		const int _gradeToExecute;


	public:

		AForm();
		AForm(std::string name, int gradeToSign, int gradeToExecute);
		AForm(const AForm& other);
		AForm& operator=(const AForm& other);
		virtual ~AForm();
		// getters
		const std::string& getName() const;
		bool isSigned() const;		int getGradeToSign() const;
		int getGradeToExecute() const;

		void	beSigned(const Bureaucrat& bureaucrat);
		virtual void execute(Bureaucrat const & executor) const = 0;

		// exceptions
		class GradeTooHighException : public std::exception {
			const char* what() const throw();
		};
		class GradeTooLowException : public std::exception {
			const char* what() const throw();
		};
		class FormNotSignedException : public std::exception {
			const char* what() const throw();
		};
};

std::ostream& operator<<(std::ostream& out, const AForm& form);