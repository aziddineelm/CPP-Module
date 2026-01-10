#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main()
{
	const Animal* j = new Dog();
	const Animal* i = new Cat();

	delete j;
	delete i;

	const int arraySize = 4;
	Animal* animals[arraySize];

	for (int idx = 0; idx < arraySize / 2; idx++)
		animals[idx] = new Dog();
	for (int idx = arraySize / 2; idx < arraySize; idx++)
		animals[idx] = new Cat();

	for (int idx = 0; idx < arraySize; idx++)
		delete animals[idx];

	return 0;
}
