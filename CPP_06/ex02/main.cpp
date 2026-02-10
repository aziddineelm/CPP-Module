#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>

Base* generate(void);
void identify(Base* p);
void identify(Base& p);

int main() {
	std::cout << "=== Type Identification Test ===" << std::endl;
	std::cout << std::endl;
	
	// Generate and test multiple random instances
	for (int i = 0; i < 5; i++) {
		std::cout << "--- Test " << (i + 1) << " ---" << std::endl;
		Base* obj = generate();
		
		std::cout << "Identify by pointer: ";
		identify(obj);
		
		std::cout << "Identify by reference: ";
		identify(*obj);
		
		delete obj;
		std::cout << std::endl;
	}
	
	// Additional specific tests
	std::cout << "=== Specific Type Tests ===" << std::endl;
	std::cout << std::endl;
	
	std::cout << "--- Testing type A ---" << std::endl;
	Base* a = new A();
	std::cout << "Pointer identification: ";
	identify(a);
	std::cout << "Reference identification: ";
	identify(*a);
	delete a;
	std::cout << std::endl;
	
	std::cout << "--- Testing type B ---" << std::endl;
	Base* b = new B();
	std::cout << "Pointer identification: ";
	identify(b);
	std::cout << "Reference identification: ";
	identify(*b);
	delete b;
	std::cout << std::endl;
	
	std::cout << "--- Testing type C ---" << std::endl;
	Base* c = new C();
	std::cout << "Pointer identification: ";
	identify(c);
	std::cout << "Reference identification: ";
	identify(*c);
	delete c;
	std::cout << std::endl;
	
	return 0;
}
