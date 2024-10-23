/*****************************************************************************
Milestone - 3
Full Name : Sergii Safronov
Student ID# : 132736224
Email : SSafronov@myseneca.ca
Section : RNB
Date : April 4, 2024

Authenticity Declaration :
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
*****************************************************************************/

#ifndef SENECA_STATION_H
#define SENECA_STATION_H

#include <iostream>

namespace seneca {

	class Station {
		
	private:
		int m_id;
		std::string m_itemName;
		std::string m_description;
		size_t m_serialNumber;
		size_t m_quantity;

		static size_t m_widthField;
		static int id_generator;

	public:
		Station(const std::string& str);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}

#endif // !SENECA_STATION_H
