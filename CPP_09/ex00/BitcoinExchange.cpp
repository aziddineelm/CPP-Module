#include "BitcoinExchange.hpp"

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

bool BitcoinExchange::isDateValid(const std::string& date) const {
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return false;

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

	int limits[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

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
	out = static_cast<float>(std::strtod(raw.c_str(), &end));
	if (*end != '\0')
		return false;

	return true;
}

float BitcoinExchange::findRate(const std::string& date) const {
	std::map<std::string, float>::const_iterator it = _rates.upper_bound(date);

	if (it == _rates.begin())
		return -1;

	--it;
	return it->second;
}

void BitcoinExchange::loadDatabase(const std::string& dbPath) {
	std::ifstream file(dbPath.c_str());
	if (!file.is_open())
		throw std::runtime_error("Error: could not open database file.");

	std::string line;
	std::getline(file, line);
	if (line != "date,exchange_rate")
		throw std::runtime_error("Error: invalid database header.");

	while (std::getline(file, line)) {
		std::string::size_type comma = line.find(',');
		if (comma == std::string::npos)
			continue;

		std::string date = line.substr(0, comma);
		std::string rateStr = line.substr(comma + 1);

		char* end;
		float rate = static_cast<float>(std::strtod(rateStr.c_str(), &end));
		if (*end == '\0')
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
	std::getline(file, line);
	if (line != "date | value") {
		std::cerr << "Error: bad input => " << line << std::endl;
		return;
	}

	while (std::getline(file, line)) {
		std::string::size_type sep = line.find(" | ");
		if (sep == std::string::npos) {
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		std::string date = line.substr(0, sep);
		std::string valStr = line.substr(sep + 3);

		if (!isDateValid(date)) {
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

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

		float rate = findRate(date);
		if (rate < 0) {
			std::cerr << "Error: date too early for database." << std::endl;
			continue;
		}

		std::cout << date << " => " << value << " = " << (value * rate) << std::endl;
	}
	file.close();
}
