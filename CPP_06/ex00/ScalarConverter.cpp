#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter& other) {
	(void)other;
}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) {
	(void)other;
	return *this;
}

ScalarConverter::~ScalarConverter() {}

//======================================================================================

bool ScalarConverter::isPseudoLiteral(const std::string& literal) {
	return (literal == "nan" || literal == "nanf"
		|| literal == "+inf" || literal == "-inf"
		|| literal == "+inff" || literal == "-inff");
}

bool ScalarConverter::isCharLiteral(const std::string& literal) {
	return (literal.length() == 1 && !std::isdigit(literal[0]));
}

void ScalarConverter::printPseudoLiteral(const std::string& literal) {
	std::string base = literal;
	if (literal == "nanf" || literal == "+inff" || literal == "-inff")
		base = literal.substr(0, literal.length() - 1);
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
	std::cout << "float: " << base << "f" << std::endl;
	std::cout << "double: " << base << std::endl;
}

void ScalarConverter::printCharLiteral(char c) {
	std::cout << "char: '" << c << "'" << std::endl;
	std::cout << "int: " << static_cast<int>(c) << std::endl;
	std::cout << "float: " << static_cast<float>(c) << ".0f" << std::endl;
	std::cout << "double: " << static_cast<double>(c) << ".0" << std::endl;
}

void ScalarConverter::printChar(double d) {
	if (d < 0 || d > 127 || std::isnan(d) || std::isinf(d))
		std::cout << "char: impossible" << std::endl;
	else if (d < 32 || d > 126)
		std::cout << "char: Non displayable" << std::endl;
	else
		std::cout << "char: '" << static_cast<char>(d) << "'" << std::endl;
}

void ScalarConverter::printInt(double d) {
	if (std::isnan(d) || std::isinf(d) || d > INT_MAX || d < INT_MIN)
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << static_cast<int>(d) << std::endl;
}

void ScalarConverter::printFloat(double d) {
	float f = static_cast<float>(d);
	std::cout << "float: " << f;
	if (f == static_cast<int>(f) && !std::isinf(f))
		std::cout << ".0f" << std::endl;
	else
		std::cout << "f" << std::endl;
}

void ScalarConverter::printDouble(double d) {
	std::cout << "double: " << d;
	if (d == static_cast<int>(d) && !std::isinf(d))
		std::cout << ".0" << std::endl;
	else
		std::cout << std::endl;
}

void ScalarConverter::convert(const std::string& literal) {
	if (literal.empty()) {
		std::cout << "Error: empty literal" << std::endl;
		return;
	}
	if (isPseudoLiteral(literal)) {
		printPseudoLiteral(literal);
		return;
	}
	if (isCharLiteral(literal)) {
		printCharLiteral(literal[0]);
		return;
	}

	char *end;
	double d = std::strtod(literal.c_str(), &end);
	if (*end != '\0' && !(*end == 'f' && *(end + 1) == '\0')) {
		std::cout << "Error: invalid literal" << std::endl;
		return;
	}

	printChar(d);
	printInt(d);
	printFloat(d);
	printDouble(d);
}
