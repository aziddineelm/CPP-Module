#include "ScalarConverter.hpp"

// Private constructor - class is not instantiable
ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter& other) {
	(void)other;
}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) {
	(void)other;
	return *this;
}

ScalarConverter::~ScalarConverter() {}

bool ScalarConverter::isDisplayable(char c) {
	return (c >= 32 && c <= 126);
}

bool ScalarConverter::isChar(const std::string& literal) {
	return (literal.length() == 3 && literal[0] == '\'' && literal[2] == '\'');
}

bool ScalarConverter::isPseudoLiteral(const std::string& literal) {
	return (literal == "nan" || literal == "nanf" || 
			literal == "+inf" || literal == "-inf" || 
			literal == "+inff" || literal == "-inff");
}

bool ScalarConverter::isInt(const std::string& literal) {
	if (literal.empty())
		return false;
	
	size_t i = 0;
	if (literal[0] == '+' || literal[0] == '-')
		i++;
	
	if (i >= literal.length())
		return false;
	
	while (i < literal.length()) {
		if (!isdigit(literal[i]))
			return false;
		i++;
	}
	return true;
}

bool ScalarConverter::isFloat(const std::string& literal) {
	if (literal.empty() || literal[literal.length() - 1] != 'f')
		return false;
	
	std::string withoutF = literal.substr(0, literal.length() - 1);
	if (withoutF.empty())
		return false;
	
	size_t i = 0;
	bool hasDot = false;
	
	if (withoutF[0] == '+' || withoutF[0] == '-')
		i++;
	
	if (i >= withoutF.length())
		return false;
	
	while (i < withoutF.length()) {
		if (withoutF[i] == '.') {
			if (hasDot)
				return false;
			hasDot = true;
		} else if (!isdigit(withoutF[i])) {
			return false;
		}
		i++;
	}
	return hasDot;
}

bool ScalarConverter::isDouble(const std::string& literal) {
	if (literal.empty())
		return false;
	
	size_t i = 0;
	bool hasDot = false;
	
	if (literal[0] == '+' || literal[0] == '-')
		i++;
	
	if (i >= literal.length())
		return false;
	
	while (i < literal.length()) {
		if (literal[i] == '.') {
			if (hasDot)
				return false;
			hasDot = true;
		} else if (!isdigit(literal[i])) {
			return false;
		}
		i++;
	}
	return hasDot;
}

void ScalarConverter::convertFromChar(const std::string& literal) {
	char c = literal[1];
	
	std::cout << "char: '" << c << "'" << std::endl;
	std::cout << "int: " << static_cast<int>(c) << std::endl;
	std::cout << "float: " << static_cast<float>(c) << ".0f" << std::endl;
	std::cout << "double: " << static_cast<double>(c) << ".0" << std::endl;
}

void ScalarConverter::convertFromInt(const std::string& literal) {
	errno = 0;
	char* endptr;
	long val = std::strtol(literal.c_str(), &endptr, 10);
	
	// Check for conversion errors
	if (errno == ERANGE || val > INT_MAX || val < INT_MIN) {
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
		return;
	}
	
	int intVal = static_cast<int>(val);
	
	// char conversion
	if (intVal < 0 || intVal > 127)
		std::cout << "char: impossible" << std::endl;
	else if (!isDisplayable(static_cast<char>(intVal)))
		std::cout << "char: Non displayable" << std::endl;
	else
		std::cout << "char: '" << static_cast<char>(intVal) << "'" << std::endl;
	
	// int conversion
	std::cout << "int: " << intVal << std::endl;
	
	// float conversion
	std::cout << "float: " << static_cast<float>(intVal);
	if (static_cast<float>(intVal) == static_cast<int>(static_cast<float>(intVal)))
		std::cout << ".0f" << std::endl;
	else
		std::cout << "f" << std::endl;
	
	// double conversion
	std::cout << "double: " << static_cast<double>(intVal);
	if (static_cast<double>(intVal) == static_cast<int>(static_cast<double>(intVal)))
		std::cout << ".0" << std::endl;
	else
		std::cout << std::endl;
}

void ScalarConverter::convertFromFloat(const std::string& literal) {
	errno = 0;
	char* endptr;
	float floatVal = std::strtof(literal.c_str(), &endptr);
	
	// Check for conversion errors
	if (errno == ERANGE && !std::isinf(floatVal)) {
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
		return;
	}
	
	// char conversion
	if (std::isnan(floatVal) || std::isinf(floatVal) || floatVal < 0 || floatVal > 127)
		std::cout << "char: impossible" << std::endl;
	else if (!isDisplayable(static_cast<char>(floatVal)))
		std::cout << "char: Non displayable" << std::endl;
	else
		std::cout << "char: '" << static_cast<char>(floatVal) << "'" << std::endl;
	
	// int conversion
	if (std::isnan(floatVal) || std::isinf(floatVal) || 
		floatVal > static_cast<float>(INT_MAX) || floatVal < static_cast<float>(INT_MIN))
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << static_cast<int>(floatVal) << std::endl;
	
	// float conversion
	std::cout << "float: " << floatVal;
	if (!std::isnan(floatVal) && !std::isinf(floatVal) && floatVal == static_cast<int>(floatVal))
		std::cout << ".0f" << std::endl;
	else
		std::cout << "f" << std::endl;
	
	// double conversion
	std::cout << "double: " << static_cast<double>(floatVal);
	if (!std::isnan(floatVal) && !std::isinf(floatVal) && floatVal == static_cast<int>(floatVal))
		std::cout << ".0" << std::endl;
	else
		std::cout << std::endl;
}

void ScalarConverter::convertFromDouble(const std::string& literal) {
	errno = 0;
	char* endptr;
	double doubleVal = std::strtod(literal.c_str(), &endptr);
	
	// Check for conversion errors
	if (errno == ERANGE && !std::isinf(doubleVal)) {
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
		return;
	}
	
	// char conversion
	if (std::isnan(doubleVal) || std::isinf(doubleVal) || doubleVal < 0 || doubleVal > 127)
		std::cout << "char: impossible" << std::endl;
	else if (!isDisplayable(static_cast<char>(doubleVal)))
		std::cout << "char: Non displayable" << std::endl;
	else
		std::cout << "char: '" << static_cast<char>(doubleVal) << "'" << std::endl;
	
	// int conversion
	if (std::isnan(doubleVal) || std::isinf(doubleVal) || 
		doubleVal > static_cast<double>(INT_MAX) || doubleVal < static_cast<double>(INT_MIN))
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << static_cast<int>(doubleVal) << std::endl;
	
	// float conversion
	std::cout << "float: " << static_cast<float>(doubleVal);
	if (!std::isnan(doubleVal) && !std::isinf(doubleVal) && doubleVal == static_cast<int>(doubleVal))
		std::cout << ".0f" << std::endl;
	else
		std::cout << "f" << std::endl;
	
	// double conversion
	std::cout << "double: " << doubleVal;
	if (!std::isnan(doubleVal) && !std::isinf(doubleVal) && doubleVal == static_cast<int>(doubleVal))
		std::cout << ".0" << std::endl;
	else
		std::cout << std::endl;
}

void ScalarConverter::handlePseudoLiteral(const std::string& literal) {
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
	
	if (literal == "nanf" || literal == "+inff" || literal == "-inff") {
		std::cout << "float: " << literal << std::endl;
		std::cout << "double: " << literal.substr(0, literal.length() - 1) << std::endl;
	} else {
		std::cout << "float: " << literal << "f" << std::endl;
		std::cout << "double: " << literal << std::endl;
	}
}

void ScalarConverter::convert(const std::string& literal) {
	if (literal.empty()) {
		std::cout << "Error: empty literal" << std::endl;
		return;
	}
	
	if (isPseudoLiteral(literal)) {
		handlePseudoLiteral(literal);
	} else if (isChar(literal)) {
		convertFromChar(literal);
	} else if (isInt(literal)) {
		convertFromInt(literal);
	} else if (isFloat(literal)) {
		convertFromFloat(literal);
	} else if (isDouble(literal)) {
		convertFromDouble(literal);
	} else {
		std::cout << "Error: invalid literal" << std::endl;
	}
}
