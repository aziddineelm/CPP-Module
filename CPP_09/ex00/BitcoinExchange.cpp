#include "BitcoinExchange.hpp"

// --- Orthodox Canonical Form ---

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const std::string& dbPath) {
	loadDatabase(dbPath);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _rates(other._rates) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
	if (this != &other)
		_rates = other._rates;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

// --- Private helpers ---

bool BitcoinExchange::isDateValid(const std::string& date) const {
	// Expected format: YYYY-MM-DD  (exactly 10 chars with dashes at pos 4 and 7)
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return false;

	// Every other character must be a digit
	for (int i = 0; i < 10; i++) {
		if (i == 4 || i == 7)
			continue;
		if (date[i] < '0' || date[i] > '9')
			return false;
	}

	int year  = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day   = std::atoi(date.substr(8, 2).c_str());

	if (month < 1 || month > 12 || day < 1)
		return false;

	// Days per month (index 0 unused)
	int limits[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	// Leap year adjustment for February
	bool leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	if (leap)
		limits[2] = 29;

	if (day > limits[month])
		return false;

	return true;
}

bool BitcoinExchange::parseValue(const std::string& raw, float& out) const {
	if (raw.empty())
		return false;

	// Check for stray characters – allow optional leading minus, digits, one dot
	bool dotSeen = false;
	std::string::size_type start = 0;
	if (raw[0] == '-' || raw[0] == '+')
		start = 1;
	if (start >= raw.length())
		return false;

	for (std::string::size_type i = start; i < raw.length(); i++) {
		if (raw[i] == '.') {
			if (dotSeen)
				return false;
			dotSeen = true;
		} else if (raw[i] < '0' || raw[i] > '9') {
			return false;
		}
	}

	char* end;
	out = std::strtof(raw.c_str(), &end);
	if (*end != '\0')
		return false;

	return true;
}

float BitcoinExchange::findRate(const std::string& date) const {
	// upper_bound returns the first element with key > date
	// decrementing it gives us the last element with key <= date
	std::map<std::string, float>::const_iterator it = _rates.upper_bound(date);

	if (it == _rates.begin())
		return -1; // date is before the earliest entry

	--it;
	return it->second;
}

// --- Public interface ---

void BitcoinExchange::loadDatabase(const std::string& dbPath) {
	std::ifstream file(dbPath.c_str());
	if (!file.is_open())
		throw std::runtime_error("Error: could not open database file.");

	std::string line;
	// Skip the header line ("date,exchange_rate")
	std::getline(file, line);

	while (std::getline(file, line)) {
		std::string::size_type comma = line.find(',');
		if (comma == std::string::npos)
			continue;

		std::string date = line.substr(0, comma);
		std::string rateStr = line.substr(comma + 1);

		char* end;
		float rate = std::strtof(rateStr.c_str(), &end);
		if (*end == '\0' || *end == '\r')
			_rates[date] = rate;
	}
	file.close();
}

void BitcoinExchange::evaluateInput(const std::string& inputPath) const {
	std::ifstream file(inputPath.c_str());
	if (!file.is_open()) {
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}

	std::string line;
	// Skip the header line ("date | value")
	std::getline(file, line);

	while (std::getline(file, line)) {
		// Find the separator " | "
		std::string::size_type sep = line.find(" | ");
		if (sep == std::string::npos) {
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		std::string date = line.substr(0, sep);
		std::string valStr = line.substr(sep + 3);

		// Validate date
		if (!isDateValid(date)) {
			std::cerr << "Error: bad input => " << date << std::endl;
			continue;
		}

		// Parse and validate value
		float value;
		if (!parseValue(valStr, value)) {
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}
		if (value < 0) {
			std::cerr << "Error: not a positive number." << std::endl;
			continue;
		}
		if (value > 1000) {
			std::cerr << "Error: too large a number." << std::endl;
			continue;
		}

		// Lookup the exchange rate
		float rate = findRate(date);
		if (rate < 0) {
			std::cerr << "Error: date too early for database." << std::endl;
			continue;
		}

		std::cout << date << " => " << value << " = " << (value * rate) << std::endl;
	}
	file.close();
}
