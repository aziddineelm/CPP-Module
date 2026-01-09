#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

void printSeparator(const std::string& title) {
	std::cout << "\n" << std::string(50, '=') << std::endl;
	std::cout << title << std::endl;
	std::cout << std::string(50, '=') << std::endl;
}

int main() {
	printSeparator("Test 1: Basic Polymorphism (from subject)");
	{
		const Animal* meta = new Animal();
		const Animal* j = new Dog();
		const Animal* i = new Cat();
		
		std::cout << "\n--- Type checking ---" << std::endl;
		std::cout << j->getType() << " " << std::endl;
		std::cout << i->getType() << " " << std::endl;
		
		std::cout << "\n--- Sound testing ---" << std::endl;
		i->makeSound(); // will output the cat sound!
		j->makeSound(); // will output the dog sound!
		meta->makeSound(); // will output generic animal sound
		
		std::cout << "\n--- Cleanup ---" << std::endl;
		delete meta;
		delete j;
		delete i;
	}

	printSeparator("Test 2: Wrong Animal/Cat (No Polymorphism)");
	{
		const WrongAnimal* wrongMeta = new WrongAnimal();
		const WrongAnimal* wrongCat = new WrongCat();
		
		std::cout << "\n--- Type checking ---" << std::endl;
		std::cout << wrongCat->getType() << " " << std::endl;
		
		std::cout << "\n--- Sound testing (notice wrong behavior) ---" << std::endl;
		wrongCat->makeSound(); // will output WrongAnimal sound (not WrongCat)!
		wrongMeta->makeSound();
		
		std::cout << "\n--- Cleanup ---" << std::endl;
		delete wrongMeta;
		delete wrongCat;
	}

	printSeparator("Test 3: Copy Constructor Testing");
	{
		Dog originalDog;
		std::cout << "\n--- Creating copy ---" << std::endl;
		Dog copyDog(originalDog);
		
		std::cout << "\n--- Both make sounds ---" << std::endl;
		originalDog.makeSound();
		copyDog.makeSound();
	}

	printSeparator("Test 4: Assignment Operator Testing");
	{
		Cat cat1;
		Cat cat2;
		
		std::cout << "\n--- Assignment ---" << std::endl;
		cat1 = cat2;
		
		std::cout << "\n--- Both make sounds ---" << std::endl;
		cat1.makeSound();
		cat2.makeSound();
	}

	printSeparator("Test 5: Array of Animals (Polymorphism)");
	{
		const Animal* animals[4];
		
		std::cout << "--- Creating array ---" << std::endl;
		animals[0] = new Dog();
		animals[1] = new Cat();
		animals[2] = new Dog();
		animals[3] = new Cat();
		
		std::cout << "\n--- All animals make sounds ---" << std::endl;
		for (int i = 0; i < 4; i++) {
			std::cout << "Animal " << i << " (" << animals[i]->getType() << "): ";
			animals[i]->makeSound();
		}
		
		std::cout << "\n--- Cleanup ---" << std::endl;
		for (int i = 0; i < 4; i++) {
			delete animals[i];
		}
	}

	printSeparator("Test 6: Direct Objects (No Pointers)");
	{
		Animal animal;
		Dog dog;
		Cat cat;
		
		std::cout << "\n--- Sounds ---" << std::endl;
		animal.makeSound();
		dog.makeSound();
		cat.makeSound();
		
		std::cout << "\n--- Automatic cleanup on scope exit ---" << std::endl;
	}

	printSeparator("Test 7: WrongCat Direct Object");
	{
		WrongAnimal wrongAnimal;
		WrongCat wrongCat;
		
		std::cout << "\n--- Direct object sounds (works correctly) ---" << std::endl;
		wrongAnimal.makeSound();
		wrongCat.makeSound(); // This works because it's called directly
		
		std::cout << "\n--- Automatic cleanup on scope exit ---" << std::endl;
	}

	printSeparator("All Tests Complete");
	
	return 0;
}
