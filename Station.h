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
