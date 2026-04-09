#pragma once

# include <iostream>

class BitcoinExchange {

	public:
		BitcoinExchange();
		// BitcoinExchange();
		BitcoinExchange (const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		~BitcoinExchange();

};