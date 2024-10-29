#include "CustomerOrder.h"
#include "Utilities.h"
#include <vector>
#include <iomanip>
#include <algorithm>

namespace seneca {

	size_t CustomerOrder::m_widthField = 0;
	
	CustomerOrder::CustomerOrder(const std::string& str) {

		Utilities util;
		size_t next_pos = 0;
		bool more = true;

		m_name = util.extractToken(str, next_pos, more);
		if (more) m_product = (util.extractToken(str, next_pos, more));

		std::vector<Item*> items;
		while (more) {
			items.push_back(new Item(util.extractToken(str, next_pos, more)));
		}
		m_cntItem = items.size();
		m_lstItem = new Item*[m_cntItem];
		for (size_t i = 0; i < m_cntItem; ++i) {
			m_lstItem[i] = items[i];
		}

		if (m_widthField < util.getFieldWidth()) {
			m_widthField = util.getFieldWidth();
		}
	}

	CustomerOrder::CustomerOrder(const CustomerOrder& other) {
		throw std::string("CustomerOrder copy constructor is not allowed!");
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept {
		*this = std::move(other);
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept {
		if (this != &other) {
			this->cleanLstItem();
			m_name = other.m_name;
			m_product = other.m_product;
			m_cntItem = other.m_cntItem;
			m_lstItem = other.m_lstItem;
			other.m_lstItem = nullptr;
			other.m_cntItem = 0;
		}
		return *this;
	}

	void CustomerOrder::cleanLstItem() {
		for (size_t i = 0; i < m_cntItem; ++i) {
			delete m_lstItem[i];
		}
		delete[] m_lstItem;
		m_lstItem = nullptr;
		m_cntItem = 0;
	}

	CustomerOrder::~CustomerOrder() {
		cleanLstItem();
	}	

	bool CustomerOrder::isOrderFilled() const {
		for (size_t i = 0; i < m_cntItem; i++) {
			if (!m_lstItem[i]->m_isFilled) {
				return false;
			}
		}
		return true;
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const {
		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled) {
				return false;
			}
		}
		return true;
	}
	
	void CustomerOrder::fillItem(Station& station, std::ostream& os) {
		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled) {
				if (station.getQuantity() > 0) {
					station.updateQuantity();
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;
					os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
					break;
				}
				else {
					os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
				}
			}
		}
	}
		
	void CustomerOrder::display(std::ostream& os)const {
		os << m_name << " - " << m_product << std::endl;		
		for (size_t i = 0; i < m_cntItem; i++) {
			os << "[" << std::setw(6) << std::setfill('0') << m_lstItem[i]-> m_serialNumber << "] " << std::setfill(' ');
			os << std::setw(m_widthField) << std::setfill(' ') << std::left << m_lstItem[i]->m_itemName << std::right;
			os << " - " << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl;
		}
	}
}
