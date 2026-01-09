#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

void printSeparator(const std::string& title) {
	std::cout << "\n" << std::string(60, '=') << std::endl;
	std::cout << title << std::endl;
	std::cout << std::string(60, '=') << std::endl;
}

int main() {
	printSeparator("Test 1: Subject Required Test");
	{
		const Animal* j = new Dog();
		const Animal* i = new Cat();
		
		delete j; // should not create a leak
		delete i;
	}

	printSeparator("Test 2: Array of Animals (Half Dogs, Half Cats)");
	{
		const int arraySize = 6;
		Animal* animals[arraySize];
		
		std::cout << "\n--- Creating array ---" << std::endl;
		for (int i = 0; i < arraySize / 2; i++) {
			std::cout << "\nCreating Dog " << i << ":" << std::endl;
			animals[i] = new Dog();
		}
		for (int i = arraySize / 2; i < arraySize; i++) {
			std::cout << "\nCreating Cat " << i << ":" << std::endl;
			animals[i] = new Cat();
		}
		
		std::cout << "\n--- All animals make sounds ---" << std::endl;
		for (int i = 0; i < arraySize; i++) {
			std::cout << animals[i]->getType() << ": ";
			animals[i]->makeSound();
		}
		
		std::cout << "\n--- Deleting animals ---" << std::endl;
		for (int i = 0; i < arraySize; i++) {
			std::cout << "\nDeleting animal " << i << ":" << std::endl;
			delete animals[i];
		}
	}

	printSeparator("Test 3: Deep Copy Test - Dog");
	{
		std::cout << "--- Creating original dog ---" << std::endl;
		Dog* originalDog = new Dog();
		originalDog->getBrain()->setIdea(0, "I love bones!");
		originalDog->getBrain()->setIdea(1, "I want to play fetch!");
		originalDog->getBrain()->setIdea(2, "Squirrel!!!");
		
		std::cout << "\n--- Creating copy using copy constructor ---" << std::endl;
		Dog* copiedDog = new Dog(*originalDog);
		
		std::cout << "\n--- Original Dog's ideas ---" << std::endl;
		std::cout << "Idea 0: " << originalDog->getBrain()->getIdea(0) << std::endl;
		std::cout << "Idea 1: " << originalDog->getBrain()->getIdea(1) << std::endl;
		std::cout << "Idea 2: " << originalDog->getBrain()->getIdea(2) << std::endl;
		
		std::cout << "\n--- Copied Dog's ideas (should be same) ---" << std::endl;
		std::cout << "Idea 0: " << copiedDog->getBrain()->getIdea(0) << std::endl;
		std::cout << "Idea 1: " << copiedDog->getBrain()->getIdea(1) << std::endl;
		std::cout << "Idea 2: " << copiedDog->getBrain()->getIdea(2) << std::endl;
		
		std::cout << "\n--- Modifying original dog's ideas ---" << std::endl;
		originalDog->getBrain()->setIdea(0, "Modified idea!");
		
		std::cout << "\n--- Checking if copy is deep (should be different) ---" << std::endl;
		std::cout << "Original Idea 0: " << originalDog->getBrain()->getIdea(0) << std::endl;
		std::cout << "Copied Idea 0: " << copiedDog->getBrain()->getIdea(0) << std::endl;
		
		std::cout << "\n--- Brain addresses (should be different) ---" << std::endl;
		std::cout << "Original Brain: " << originalDog->getBrain() << std::endl;
		std::cout << "Copied Brain: " << copiedDog->getBrain() << std::endl;
		
		std::cout << "\n--- Cleanup ---" << std::endl;
		delete originalDog;
		delete copiedDog;
	}

	printSeparator("Test 4: Deep Copy Test - Cat with Assignment");
	{
		std::cout << "--- Creating two cats ---" << std::endl;
		Cat* cat1 = new Cat();
		Cat* cat2 = new Cat();
		
		cat1->getBrain()->setIdea(0, "I need food!");
		cat1->getBrain()->setIdea(1, "Nap time!");
		
		cat2->getBrain()->setIdea(0, "Different cat thoughts");
		
		std::cout << "\n--- Before assignment ---" << std::endl;
		std::cout << "Cat1 Idea 0: " << cat1->getBrain()->getIdea(0) << std::endl;
		std::cout << "Cat2 Idea 0: " << cat2->getBrain()->getIdea(0) << std::endl;
		std::cout << "Cat1 Brain: " << cat1->getBrain() << std::endl;
		std::cout << "Cat2 Brain: " << cat2->getBrain() << std::endl;
		
		std::cout << "\n--- Assigning cat1 to cat2 ---" << std::endl;
		*cat2 = *cat1;
		
		std::cout << "\n--- After assignment (ideas should match) ---" << std::endl;
		std::cout << "Cat1 Idea 0: " << cat1->getBrain()->getIdea(0) << std::endl;
		std::cout << "Cat2 Idea 0: " << cat2->getBrain()->getIdea(0) << std::endl;
		
		std::cout << "\n--- Modifying cat1 ---" << std::endl;
		cat1->getBrain()->setIdea(0, "Changed after assignment");
		
		std::cout << "\n--- Checking deep copy (should be different) ---" << std::endl;
		std::cout << "Cat1 Idea 0: " << cat1->getBrain()->getIdea(0) << std::endl;
		std::cout << "Cat2 Idea 0: " << cat2->getBrain()->getIdea(0) << std::endl;
		std::cout << "Cat1 Brain: " << cat1->getBrain() << std::endl;
		std::cout << "Cat2 Brain: " << cat2->getBrain() << std::endl;
		
		std::cout << "\n--- Cleanup ---" << std::endl;
		delete cat1;
		delete cat2;
	}

	printSeparator("Test 5: Stack vs Heap Objects");
	{
		std::cout << "--- Creating stack Dog ---" << std::endl;
		Dog stackDog;
		stackDog.getBrain()->setIdea(0, "Stack dog idea");
		
		std::cout << "\n--- Creating heap Dog ---" << std::endl;
		Dog* heapDog = new Dog();
		heapDog->getBrain()->setIdea(0, "Heap dog idea");
		
		std::cout << "\n--- Both make sounds ---" << std::endl;
		stackDog.makeSound();
		heapDog->makeSound();
		
		std::cout << "\n--- Deleting heap dog ---" << std::endl;
		delete heapDog;
		
		std::cout << "\n--- Stack dog cleanup on scope exit ---" << std::endl;
	}

	printSeparator("All Tests Complete - No Memory Leaks!");
	
	return 0;
}
