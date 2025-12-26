#include "Zombie.hpp"

int main( void ) {
	Zombie* zm = zombieHorde(4, "new");

	for (int i = 0; i < 4; i++) {
		zm[i].announce();
	}

	delete[] zm;
	return 0;
}