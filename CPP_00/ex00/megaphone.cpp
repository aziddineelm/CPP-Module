#include <iostream>

int main(int ac, char **av) {
	if (ac == 1)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *\n";
		return 1;
	}
	for (int i = 1; av[i]; i++) {
		for (int j = 0; av[i][j]; j++) {
			if (av[i][j] >= 'a' && av[i][j] <= 'z')
				av[i][j] -= 32;
			else if (av[i][j] >= 'A' && av[i][j] <= 'Z')
				av[i][j] += 32;
			std::cout << av[i][j];
		}
	}
	std::cout << std::endl;
	return 0;
}