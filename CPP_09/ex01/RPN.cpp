#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN& other) : _stk(other._stk) {}

RPN& RPN::operator=(const RPN& other) {
	if (this != &other)
		_stk = other._stk;
	return *this;
}

RPN::~RPN() {}

bool RPN::isOperator(const std::string& token) const {
	return (token == "+" || token == "-" || token == "*" || token == "/");
}

long RPN::applyOp(long left, long right, const std::string& op) const {
	if (op == "+")
		return left + right;
	if (op == "-")
		return left - right;
	if (op == "*")
		return left * right;
	if (op == "/") {
		if (right == 0)
			throw std::runtime_error("Error");
		return left / right;
	}
	throw std::runtime_error("Error");
}

long RPN::evaluate(const std::string& expression) {
	std::istringstream	stream(expression);
	std::string			token;

	while (stream >> token) {
		if (isOperator(token)) {
			// need at least two numbers on the stack to apply an operator
			if (_stk.size() < 2)
				throw std::runtime_error("Error");

			long right = _stk.top();
			_stk.pop();
			long left = _stk.top();
			_stk.pop();

			_stk.push(applyOp(left, right, token));
		} else {
			// token must be a single-digit number (0 through 9)
			if (token.length() != 1 || token[0] < '0' || token[0] > '9')
				throw std::runtime_error("Error");
			_stk.push(token[0] - '0');
		}
	}

	// after processing all tokens, exactly one result should remain
	if (_stk.size() != 1)
		throw std::runtime_error("Error");

	long result = _stk.top();
	_stk.pop();
	return result;
}
