#pragma once

# include <iostream>
# include <vector>
# include <deque>
# include <ctime>
# include <cstdlib>
# include <stdexcept>
# include <algorithm>
# include <utility>
# include <iomanip>

class PmergeMe {

	private:
		std::vector<int>	_vec;
		std::deque<int>		_deq;

		static std::vector<int>	jacobsthalOrder(int n);

		void	sortVec(std::vector<int>& arr);
		void	sortDeq(std::deque<int>& arr);

	public:
		PmergeMe();
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& other);
		~PmergeMe();

		void	parseAndSort(int ac, char **av);
};
