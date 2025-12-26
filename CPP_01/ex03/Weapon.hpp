#pragma once

#include <iostream>
#include <string>

class Weapon {
	private:
		std::string _type;
	public:
		Weapon( std::string type);
		~Weapon();
		const std::string& getType() const;
		void setType( std::string newType);
};