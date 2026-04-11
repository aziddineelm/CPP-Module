#pragma once

# include <iostream>
# include <sstream>
# include <stack>
# include <cstdlib>

class RPN {

	private:
		std::stack<long>	_stk;

		bool	isOperator(const std::string& token) const;
		long	applyOp(long left, long right, const std::string& op) const;

	public:
		RPN();
		RPN(const RPN& other);
		RPN& operator=(const RPN& other);
		~RPN();

		long	evaluate(const std::string& expression);
};
