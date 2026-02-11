#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>
#include <iostream>
#include <cstdlib>
#include <climits>
#include <cmath>

class ScalarConverter {
private:
	ScalarConverter();
	ScalarConverter(const ScalarConverter& other);
	ScalarConverter& operator=(const ScalarConverter& other);
	~ScalarConverter();

	static bool isPseudoLiteral(const std::string& literal);
	static bool isCharLiteral(const std::string& literal);
	static void printPseudoLiteral(const std::string& literal);
	static void printCharLiteral(char c);
	static void printChar(double d);
	static void printInt(double d);
	static void printFloat(double d);
	static void printDouble(double d);

public:
	static void convert(const std::string& literal);
};

#endif
