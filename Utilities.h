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

#ifndef SENECA_UTILITIES_H
#define SENECA_UTILITIES_H

#include <iostream>

namespace seneca {

	class Utilities {

	private:
		size_t m_widthField = 1;
		static char m_delimiter;

	public:
		void setFieldWidth(size_t newWidth);
		size_t getFieldWidth() const;
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
		
		static void setDelimiter(char newDelimiter);
		static char getDelimiter();

		void trim(std::string& str);
	};
}

#endif // !SENECA_UTILITIES_H
