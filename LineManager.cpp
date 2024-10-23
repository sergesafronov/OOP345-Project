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

#include "LineManager.h"
#include <fstream>
#include <sstream>
#include <algorithm>

namespace seneca {	

    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
        std::ifstream f(file);
        if (!f) {
            throw std::string("Unable to open file: " + file);
        }

        std::string record;
        while (std::getline(f, record)) {
            size_t next_pos = 0;
            bool more = true;
            Utilities util;

            std::string active = util.extractToken(record, next_pos, more);
            std::string next = more ? util.extractToken(record, next_pos, more) : "";

            auto findStationByName = [&](const std::string& name) -> Workstation* {
                auto it = std::find_if(stations.begin(), stations.end(),
                                       [&](const Workstation* ws) { return ws->getItemName() == name; });
                return it != stations.end() ? *it : nullptr;
            };

            Workstation* activeStation = findStationByName(active);
            Workstation* nextStation = findStationByName(next);

            if (activeStation) {
                m_activeLine.push_back(activeStation);
                activeStation->setNextStation(nextStation);
            }
        }
        f.close();

        auto isNotNextStation = [&](const Workstation* station) {
            return std::none_of(m_activeLine.begin(), m_activeLine.end(),
                                [&](const Workstation* ws) { return ws->getNextStation() == station; });
        };

        auto itFirstStation = std::find_if(m_activeLine.begin(), m_activeLine.end(), isNotNextStation);
        if (itFirstStation != m_activeLine.end()) {
            m_firstStation = *itFirstStation;
        }
        
        m_cntCustomerOrder = g_pending.size();
    }
	
	void LineManager::reorderStations() {
		std::vector<Workstation*> temp;
		Workstation* station = m_firstStation;
		while (station) {
			temp.push_back(station);
			station = station->getNextStation();
		}
		m_activeLine = std::move(temp);
	}

	bool LineManager::run(std::ostream& os) {
		static size_t count = 0;
		count++;
		os << "Line Manager Iteration: " << count << std::endl;

		if (!g_pending.empty()) {
			*m_firstStation += std::move(g_pending.front());
			g_pending.pop_front();
		}

		for (auto al : m_activeLine) {
			al->fill(os);
		}

		for (auto al : m_activeLine) {
			al->attemptToMoveOrder();
		}
		
		return m_cntCustomerOrder == (g_completed.size() + g_incomplete.size());
	}

	void LineManager::display(std::ostream& os) const {
		for (const auto& al : m_activeLine) {
			al->display(os);
		}
	}
}