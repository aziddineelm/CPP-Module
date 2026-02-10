#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

Base* generate(void) {
	// Seed random number generator only once
	static bool seeded = false;
	if (!seeded) {
		std::srand(std::time(NULL));
		seeded = true;
	}
	
	int random = std::rand() % 3;
	
	switch (random) {
		case 0:
			std::cout << "[Generated type A]" << std::endl;
			return new A();
		case 1:
			std::cout << "[Generated type B]" << std::endl;
			return new B();
		case 2:
			std::cout << "[Generated type C]" << std::endl;
			return new C();
		default:
			return NULL;
	}
}

void identify(Base* p) {
	// Use dynamic_cast to check the actual type
	// dynamic_cast returns NULL if the cast fails
	if (dynamic_cast<A*>(p)) {
		std::cout << "A" << std::endl;
	} else if (dynamic_cast<B*>(p)) {
		std::cout << "B" << std::endl;
	} else if (dynamic_cast<C*>(p)) {
		std::cout << "C" << std::endl;
	} else {
		std::cout << "Unknown type" << std::endl;
	}
}

void identify(Base& p) {
	// Use dynamic_cast with references
	// dynamic_cast throws std::bad_cast exception if the cast fails
	// We cannot use pointers inside this function
	
	try {
		(void)dynamic_cast<A&>(p);
		std::cout << "A" << std::endl;
		return;
	} catch (std::exception&) {
		// Not type A, continue checking
	}
	
	try {
		(void)dynamic_cast<B&>(p);
		std::cout << "B" << std::endl;
		return;
	} catch (std::exception&) {
		// Not type B, continue checking
	}
	
	try {
		(void)dynamic_cast<C&>(p);
		std::cout << "C" << std::endl;
		return;
	} catch (std::exception&) {
		// Not type C either
	}
	
	std::cout << "Unknown type" << std::endl;
}
