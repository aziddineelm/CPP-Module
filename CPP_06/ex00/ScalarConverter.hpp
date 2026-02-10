#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>
#include <iostream>
#include <limits>
#include <cmath>
#include <cstdlib>
#include <cerrno>
#include <climits>

class ScalarConverter {
private:
	// Private constructor to prevent instantiation
	ScalarConverter();
	ScalarConverter(const ScalarConverter& other);
	ScalarConverter& operator=(const ScalarConverter& other);
	~ScalarConverter();

	// Helper methods
	static bool isChar(const std::string& literal);
	static bool isInt(const std::string& literal);
	static bool isFloat(const std::string& literal);
	static bool isDouble(const std::string& literal);
	static bool isPseudoLiteral(const std::string& literal);
	
	static void convertFromChar(const std::string& literal);
	static void convertFromInt(const std::string& literal);
	static void convertFromFloat(const std::string& literal);
	static void convertFromDouble(const std::string& literal);
	static void handlePseudoLiteral(const std::string& literal);
	
	static bool isDisplayable(char c);

public:
	static void convert(const std::string& literal);
};

#endif
