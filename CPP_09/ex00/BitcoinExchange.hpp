#pragma once

# include <iostream>
# include <fstream>
# include <cstdlib>
# include <stdexcept>
# include <map>

class BitcoinExchange {

	private:
		std::map<std::string, float>	_rates;

		bool	isDateValid(const std::string& date) const;
		bool	parseValue(const std::string& raw, float& out) const;
		float	findRate(const std::string& date) const;

	public:
		BitcoinExchange();
		BitcoinExchange(const std::string& dbPath);
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		~BitcoinExchange();

		void	loadDatabase(const std::string& dbPath);
		void	evaluateInput(const std::string& inputPath) const;
};