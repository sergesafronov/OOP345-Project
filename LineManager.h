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
