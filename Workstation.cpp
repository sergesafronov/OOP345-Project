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

#include "Workstation.h"
#include <iostream>

namespace seneca {

    std::deque<CustomerOrder> g_pending;
    std::deque<CustomerOrder> g_completed;
    std::deque<CustomerOrder> g_incomplete;
    
    Workstation::Workstation(const std::string& record) : Station(record) {}
   
    void Workstation::fill(std::ostream& os) {
        if (!m_orders.empty()) {
            m_orders.front().fillItem(*this, os);
        }
    }

    bool Workstation::attemptToMoveOrder() {
        if (!m_orders.empty()) {
            if (m_orders.front().isItemFilled(getItemName()) || getQuantity() == 0) {
                if (getNextStation()) {
                    *getNextStation() += std::move(m_orders.front());
                }
                else {
                    if (m_orders.front().isOrderFilled()) {
                        g_completed.push_back(std::move(m_orders.front()));
                    }
                    else {
                        g_incomplete.push_back(std::move(m_orders.front()));
                    }
                }
                m_orders.pop_front(); 
                return true; 
            }
        }
        return false; 
    }

    void Workstation::setNextStation(Workstation* station) {
        m_pNextStation = station;
    }

    Workstation* Workstation::getNextStation()const {
        return m_pNextStation;
    }

    void Workstation::display(std::ostream& os)const {
        os << getItemName() << " --> ";
        if (getNextStation()) {
            os << getNextStation()->getItemName();
        }
        else {
            os << "End of Line";
        }
        os << std::endl;
    }

    Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
        m_orders.push_back(std::move(newOrder));
        return *this;
    }
}