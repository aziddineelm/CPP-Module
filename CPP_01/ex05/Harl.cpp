#include "Harl.hpp"

Harl::Harl() {}
Harl::~Harl() {}

void Harl::debug() {
	std::cout << "[ DEBUG ]" << std::endl;
	std::cout << "This is a Debug Messaage" << std::endl;
}

void Harl::info() {
	std::cout << "[ INFO ]" << std::endl;
	std::cout << "This is an Info Messaage" << std::endl;
}

void Harl::warning() {
	std::cout << "[ WARNING ]" << std::endl;
	std::cout << "This is a Warning Messaage" << std::endl;
}

void Harl::error() {
	std::cout << "[ ERROR ]" << std::endl;
	std::cout << "This is an Error Message" << std::endl;
}

void Harl::complain( std::string level ) {
	void (Harl::*funcs[])(void) = {
        &Harl::warning,
        &Harl::debug,
        &Harl::error,
        &Harl::info
    };
	std::string levels[] = {
		"WARNING", "DEBUG", "ERROR", "INFO"
	};
	for (int i = 0; i < 4; i++) {
		if (levels[i] == level) {
			(this->*funcs[i])();
			return;
		}
	}
}