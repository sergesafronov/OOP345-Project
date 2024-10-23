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

#include "Utilities.h"

namespace seneca {

    char Utilities::m_delimiter = ',';

	void Utilities::setFieldWidth(size_t newWidth) {
		m_widthField = newWidth;
	}

	size_t Utilities::getFieldWidth() const {
		return m_widthField;
	}

	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
        
        more = false; 
        
        size_t end_pos = str.find(m_delimiter, next_pos);

        if (end_pos == next_pos) {
            throw std::string("No token between delimiters");
        }

        if (end_pos == std::string::npos) {
            end_pos = str.size();
            more = false;
        }
        else {
            more = true;
        }

        std::string token = str.substr(next_pos, end_pos - next_pos);
        next_pos = end_pos + 1;

        trim(token);

        if (m_widthField < token.length()) {
            m_widthField = token.length();
        }

        return token;
	}

	void Utilities::setDelimiter(char newDelimiter) {
        m_delimiter = newDelimiter;
	}

	char Utilities::getDelimiter() {
		return 0;
	}

    void Utilities::trim(std::string& str) {
        str.erase(0, str.find_first_not_of(' '));
        str.erase(str.find_last_not_of(' ') + 1);
    }
}
