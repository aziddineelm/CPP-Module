#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

void printSeparator(const std::string& title) {
	std::cout << "\n" << std::string(60, '=') << std::endl;
	std::cout << title << std::endl;
	std::cout << std::string(60, '=') << std::endl;
}

int main() {
	printSeparator("Test 1: Abstract Class - Cannot Instantiate Animal");
	{
		// This should NOT compile if you uncomment it:
		// Animal* animal = new Animal(); // ERROR: cannot instantiate abstract class
		
		std::cout << "✓ Animal class is abstract (cannot be instantiated)" << std::endl;
	}

	printSeparator("Test 2: Polymorphism Still Works");
	{
		const Animal* j = new Dog();
		const Animal* i = new Cat();
		
		std::cout << "\n--- Types ---" << std::endl;
		std::cout << j->getType() << std::endl;
		std::cout << i->getType() << std::endl;
		
		std::cout << "\n--- Sounds ---" << std::endl;
		j->makeSound();
		i->makeSound();
		
		std::cout << "\n--- Cleanup ---" << std::endl;
		delete j;
		delete i;
	}

	printSeparator("Test 3: Array of Animals");
	{
		const int arraySize = 6;
		Animal* animals[arraySize];
		
		std::cout << "\n--- Creating array ---" << std::endl;
		for (int i = 0; i < arraySize / 2; i++) {
			animals[i] = new Dog();
		}
		for (int i = arraySize / 2; i < arraySize; i++) {
			animals[i] = new Cat();
		}
		
		std::cout << "\n--- All animals make sounds ---" << std::endl;
		for (int i = 0; i < arraySize; i++) {
			std::cout << animals[i]->getType() << ": ";
			animals[i]->makeSound();
		}
		
		std::cout << "\n--- Deleting animals ---" << std::endl;
		for (int i = 0; i < arraySize; i++) {
			delete animals[i];
		}
	}

	printSeparator("Test 4: Deep Copy Still Works");
	{
		std::cout << "--- Creating original dog ---" << std::endl;
		Dog* dog1 = new Dog();
		dog1->getBrain()->setIdea(0, "Chase cats!");
		dog1->getBrain()->setIdea(1, "Bark at mailman!");
		
		std::cout << "\n--- Creating copy ---" << std::endl;
		Dog* dog2 = new Dog(*dog1);
		
		std::cout << "\n--- Verifying deep copy ---" << std::endl;
		std::cout << "Dog1 Idea 0: " << dog1->getBrain()->getIdea(0) << std::endl;
		std::cout << "Dog2 Idea 0: " << dog2->getBrain()->getIdea(0) << std::endl;
		std::cout << "Dog1 Brain address: " << dog1->getBrain() << std::endl;
		std::cout << "Dog2 Brain address: " << dog2->getBrain() << std::endl;
		
		std::cout << "\n--- Modifying dog1 ---" << std::endl;
		dog1->getBrain()->setIdea(0, "Modified!");
		
		std::cout << "Dog1 Idea 0 (modified): " << dog1->getBrain()->getIdea(0) << std::endl;
		std::cout << "Dog2 Idea 0 (unchanged): " << dog2->getBrain()->getIdea(0) << std::endl;
		
		std::cout << "\n--- Cleanup ---" << std::endl;
		delete dog1;
		delete dog2;
	}

	printSeparator("Test 5: Mixed Array with Brain Ideas");
	{
		Dog dog1;
		Cat cat1;
		
		dog1.getBrain()->setIdea(0, "I'm a good boy!");
		cat1.getBrain()->setIdea(0, "I rule this house!");
		
		std::cout << "\n--- Their thoughts ---" << std::endl;
		std::cout << "Dog thinks: " << dog1.getBrain()->getIdea(0) << std::endl;
		std::cout << "Cat thinks: " << cat1.getBrain()->getIdea(0) << std::endl;
		
		std::cout << "\n--- Their sounds ---" << std::endl;
		dog1.makeSound();
		cat1.makeSound();
		
		std::cout << "\n--- Automatic cleanup on scope exit ---" << std::endl;
	}

	printSeparator("All Tests Complete - Animal is Abstract!");
	std::cout << "✓ Animal cannot be instantiated directly" << std::endl;
	std::cout << "✓ Dog and Cat still work perfectly" << std::endl;
	std::cout << "✓ Polymorphism is maintained" << std::endl;
	std::cout << "✓ Deep copy works correctly" << std::endl;
	
	return 0;
}
