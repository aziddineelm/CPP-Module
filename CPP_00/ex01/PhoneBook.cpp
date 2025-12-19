#include "PhoneBook.hpp"
#include "Contact.hpp"

PhoneBook::PhoneBook() {
	index = 0;
	count = 0;
}

void PhoneBook::addContact() {
    contact[index].setInfo();
    index = (index + 1) % 8;
    if (count < 8)
        count++;
}

void PhoneBook::searchContact() {

}
