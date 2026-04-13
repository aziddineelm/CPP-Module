#include "PmergeMe.hpp"

// --- Orthodox Canonical Form ---

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other) : _vec(other._vec), _deq(other._deq) {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
	if (this != &other) {
		_vec = other._vec;
		_deq = other._deq;
	}
	return *this;
}

PmergeMe::~PmergeMe() {}

// --- Jacobsthal insertion order ---
// Generates the order in which pend elements should be inserted
// to minimize the total number of binary search comparisons.
// For n pend elements, returns indices [0..n-1] in Jacobsthal order.

std::vector<int> PmergeMe::jacobsthalOrder(int n) {
	std::vector<int> order;
	if (n <= 0)
		return order;

	// pend[0] (= b2) is always inserted first
	order.push_back(0);
	if (n == 1)
		return order;

	// Build Jacobsthal numbers: 0, 1, 1, 3, 5, 11, 21, 43, ...
	std::vector<int> jn;
	jn.push_back(0);
	jn.push_back(1);
	while (jn.back() < n) {
		int sz = jn.size();
		jn.push_back(jn[sz - 1] + 2 * jn[sz - 2]);
	}

	// Each group inserts from jn[k]-1 down to jn[k-1]
	// This "right to left" order within groups minimizes comparisons
	for (size_t k = 3; k < jn.size(); k++) {
		int high = jn[k];
		if (high > n)
			high = n;
		int low = jn[k - 1];
		for (int i = high - 1; i >= low; i--)
			order.push_back(i);
		if (high >= n)
			break;
	}
	return order;
}

// --- Ford-Johnson sort for std::vector ---

void PmergeMe::sortVec(std::vector<int>& arr) {
	if (arr.size() <= 1)
		return;

	// Step 1: Save straggler if odd count
	bool hasStraggler = (arr.size() % 2 != 0);
	int straggler = 0;
	if (hasStraggler)
		straggler = arr.back();

	// Step 2: Pair adjacent elements, larger first
	std::vector<std::pair<int, int> > pairs;
	for (size_t i = 0; i + 1 < arr.size(); i += 2) {
		if (arr[i] > arr[i + 1])
			pairs.push_back(std::make_pair(arr[i], arr[i + 1]));
		else
			pairs.push_back(std::make_pair(arr[i + 1], arr[i]));
	}

	// Step 3: Extract winners (larger of each pair) and sort recursively
	std::vector<int> winners;
	for (size_t i = 0; i < pairs.size(); i++)
		winners.push_back(pairs[i].first);
	sortVec(winners);

	// Step 4: Reorder pairs to match the sorted winners
	std::vector<std::pair<int, int> > sorted;
	std::vector<bool> used(pairs.size(), false);
	for (size_t i = 0; i < winners.size(); i++) {
		for (size_t j = 0; j < pairs.size(); j++) {
			if (!used[j] && pairs[j].first == winners[i]) {
				sorted.push_back(pairs[j]);
				used[j] = true;
				break;
			}
		}
	}

	// Step 5: Build main chain — b1 goes first, then all winners
	// b1 < a1 (guaranteed by pairing), and a1 < a2 < ... (sorted)
	std::vector<int> chain;
	chain.push_back(sorted[0].second);
	for (size_t i = 0; i < sorted.size(); i++)
		chain.push_back(sorted[i].first);

	// Step 6: Collect remaining pend elements (b2, b3, ...)
	std::vector<int> pend;
	for (size_t i = 1; i < sorted.size(); i++)
		pend.push_back(sorted[i].second);

	// Step 7: Insert pend elements in Jacobsthal order using binary search
	std::vector<int> order = jacobsthalOrder(pend.size());
	for (size_t i = 0; i < order.size(); i++) {
		int val = pend[order[i]];
		std::vector<int>::iterator pos = std::lower_bound(chain.begin(), chain.end(), val);
		chain.insert(pos, val);
	}

	// Step 8: Insert straggler if it exists
	if (hasStraggler) {
		std::vector<int>::iterator pos = std::lower_bound(chain.begin(), chain.end(), straggler);
		chain.insert(pos, straggler);
	}

	arr = chain;
}

// --- Ford-Johnson sort for std::deque ---

void PmergeMe::sortDeq(std::deque<int>& arr) {
	if (arr.size() <= 1)
		return;

	bool hasStraggler = (arr.size() % 2 != 0);
	int straggler = 0;
	if (hasStraggler)
		straggler = arr.back();

	std::deque<std::pair<int, int> > pairs;
	for (size_t i = 0; i + 1 < arr.size(); i += 2) {
		if (arr[i] > arr[i + 1])
			pairs.push_back(std::make_pair(arr[i], arr[i + 1]));
		else
			pairs.push_back(std::make_pair(arr[i + 1], arr[i]));
	}

	std::deque<int> winners;
	for (size_t i = 0; i < pairs.size(); i++)
		winners.push_back(pairs[i].first);
	sortDeq(winners);

	std::deque<std::pair<int, int> > sorted;
	std::deque<bool> used(pairs.size(), false);
	for (size_t i = 0; i < winners.size(); i++) {
		for (size_t j = 0; j < pairs.size(); j++) {
			if (!used[j] && pairs[j].first == winners[i]) {
				sorted.push_back(pairs[j]);
				used[j] = true;
				break;
			}
		}
	}

	std::deque<int> chain;
	chain.push_back(sorted[0].second);
	for (size_t i = 0; i < sorted.size(); i++)
		chain.push_back(sorted[i].first);

	std::deque<int> pend;
	for (size_t i = 1; i < sorted.size(); i++)
		pend.push_back(sorted[i].second);

	std::vector<int> order = jacobsthalOrder(pend.size());
	for (size_t i = 0; i < order.size(); i++) {
		int val = pend[order[i]];
		std::deque<int>::iterator pos = std::lower_bound(chain.begin(), chain.end(), val);
		chain.insert(pos, val);
	}

	if (hasStraggler) {
		std::deque<int>::iterator pos = std::lower_bound(chain.begin(), chain.end(), straggler);
		chain.insert(pos, straggler);
	}

	arr = chain;
}

// --- Parse input and run both sorts ---

void PmergeMe::parseAndSort(int ac, char **av) {
	// Parse and validate arguments
	for (int i = 1; i < ac; i++) {
		std::string arg(av[i]);
		if (arg.empty())
			throw std::runtime_error("Error");
		for (size_t j = 0; j < arg.size(); j++) {
			if (arg[j] < '0' || arg[j] > '9')
				throw std::runtime_error("Error");
		}
		long val = std::atol(arg.c_str());
		if (val <= 0 || val > 2147483647)
			throw std::runtime_error("Error");
		_vec.push_back(static_cast<int>(val));
		_deq.push_back(static_cast<int>(val));
	}

	// Display unsorted sequence
	std::cout << "Before:";
	for (size_t i = 0; i < _vec.size(); i++)
		std::cout << " " << _vec[i];
	std::cout << std::endl;

	// Sort with std::vector and measure time
	clock_t vStart = clock();
	sortVec(_vec);
	clock_t vEnd = clock();
	double vecTime = static_cast<double>(vEnd - vStart) / CLOCKS_PER_SEC * 1000000;

	// Sort with std::deque and measure time
	clock_t dStart = clock();
	sortDeq(_deq);
	clock_t dEnd = clock();
	double deqTime = static_cast<double>(dEnd - dStart) / CLOCKS_PER_SEC * 1000000;

	// Display sorted sequence
	std::cout << "After:";
	for (size_t i = 0; i < _vec.size(); i++)
		std::cout << " " << _vec[i];
	std::cout << std::endl;

	// Display timing
	std::cout << std::fixed << std::setprecision(5);
	std::cout << "Time to process a range of " << _vec.size()
		<< " elements with std::vector : " << vecTime << " us" << std::endl;
	std::cout << "Time to process a range of " << _deq.size()
		<< " elements with std::deque  : " << deqTime << " us" << std::endl;
}
