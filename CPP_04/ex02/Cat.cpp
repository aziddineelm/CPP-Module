#include "Cat.hpp"

Cat::Cat() {
	this->type = "Cat";
	this->brain = new Brain();
	std::cout << "🐈 Cat default constructor called" << std::endl;
}

Cat::Cat(const Cat& other) : Animal(other) {
	std::cout << "🐈 Cat copy constructor called" << std::endl;
	this->brain = new Brain(*other.brain);
}

Cat& Cat::operator=(const Cat& other) {
	std::cout << "🐈 Cat assignment operator called" << std::endl;
	if (this != &other) {
		Animal::operator=(other);
		delete this->brain;
		this->brain = new Brain(*other.brain);
	}
	return *this;
}

Cat::~Cat() {
	delete this->brain;
	std::cout << "🐈 Cat destructor called" << std::endl;
}

void Cat::makeSound() const {
	std::cout << "Meow! Meow! 🐱" << std::endl;
}

Brain* Cat::getBrain() const {
	return this->brain;
}
