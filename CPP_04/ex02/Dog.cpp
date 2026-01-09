#include "Dog.hpp"

Dog::Dog() {
	this->type = "Dog";
	this->brain = new Brain();
	std::cout << "🐕 Dog default constructor called" << std::endl;
}

Dog::Dog(const Dog& other) : Animal(other) {
	std::cout << "🐕 Dog copy constructor called" << std::endl;
	this->brain = new Brain(*other.brain);
}

Dog& Dog::operator=(const Dog& other) {
	std::cout << "🐕 Dog assignment operator called" << std::endl;
	if (this != &other) {
		Animal::operator=(other);
		delete this->brain;
		this->brain = new Brain(*other.brain);
	}
	return *this;
}

Dog::~Dog() {
	delete this->brain;
	std::cout << "🐕 Dog destructor called" << std::endl;
}

void Dog::makeSound() const {
	std::cout << "Woof! Woof! 🐶" << std::endl;
}

Brain* Dog::getBrain() const {
	return this->brain;
}
