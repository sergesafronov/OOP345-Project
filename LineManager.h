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

#ifndef SENECA_LINEMANAGER_H
#define SENECA_LINEMANAGER_H

#include <vector>
#include <deque>
#include <string>
#include <iostream>
#include "Workstation.h"
#include "Utilities.h"

namespace seneca {

    class LineManager {
        
        std::vector<Workstation*> m_activeLine {};
        size_t m_cntCustomerOrder {};
        Workstation* m_firstStation {};

    public:
        LineManager(const std::string& file, const std::vector<Workstation*>& stations);
       
        void reorderStations();
        bool run(std::ostream& os);
        void display(std::ostream& os) const;
    };}

#endif // SENECA_LINEMANAGER_H
