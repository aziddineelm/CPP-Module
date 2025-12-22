#include "Account.hpp"
#include <ctime>
#include <iostream>	

Account::Account( int initial_deposit ) : _accountIndex(_nbAccounts), _amount(initial_deposit), _nbDeposits(0), _nbWithdrawals(0)
{
	_nbAccounts++;
	_totalAmount += _amount;
	_displayTimestamp();
	std::cout	<< "index:" << _accountIndex << ";" << "amount:" << _amount << ";" << "created" << std::endl;
}

Account::~Account( void ) {
	_displayTimestamp();
	std::cout	<< "index:" << _accountIndex << ";" << "amount:" << _amount << ";" << "closed" << std::endl;
	_nbAccounts--;
    _totalAmount -= _amount;
}

void	Account::_displayTimestamp( void ) {
	time_t now = time(0);
    struct tm tstruct = *localtime(&now);
    char buf[20];
    strftime(buf, sizeof(buf), "%Y%m%d_%H%M%S", &tstruct);
    std::cout << "[" << buf << "] ";
}