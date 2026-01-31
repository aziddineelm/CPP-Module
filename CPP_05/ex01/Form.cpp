#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form() : _name("Default Form"), _isSigned(false), _gradeToSign(150), _gradeToExecute(150) {}

Form::Form(std::string name, int gradeToSign, int gradeToExecute) 
	: _name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute) {
	if (gradeToSign < 1 || gradeToExecute < 1) {
		throw GradeTooHighException();
	}
	if (gradeToSign > 150 || gradeToExecute > 150) {
		throw GradeTooLowException();
	}
}

Form::Form(const Form& other) 
	: _name(other._name), _isSigned(other._isSigned), 
	  _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute) {}

Form& Form::operator=(const Form& other) {
	if (this != &other)
		this->_isSigned = other._isSigned;
	return *this;
}

Form::~Form() {}

std::string Form::getName() const {
	return _name;
}

bool Form::isSigned() const {
	return _isSigned;
}

int Form::getGradeToSign() const {
	return _gradeToSign;
}

int Form::getGradeToExecute() const {
	return _gradeToExecute;
}

void Form::beSigned(const Bureaucrat& bureaucrat) {
	if (bureaucrat.getGrade() > _gradeToSign) {
		throw GradeTooLowException();
	}
	_isSigned = true;
}

const char* Form::GradeTooHighException::what() const throw() {
	return "Form grade is too high! Maximum grade is 1.";
}

const char* Form::GradeTooLowException::what() const throw() {
	return "Form grade is too low! Minimum grade is 150.";
}

std::ostream& operator<<(std::ostream& out, const Form& form) {
	out << "Form " << form.getName() 
	    << " [Signed: " << (form.isSigned() ? "Yes" : "No")
	    << ", Grade to sign: " << form.getGradeToSign()
	    << ", Grade to execute: " << form.getGradeToExecute() << "]";
	return out;
}