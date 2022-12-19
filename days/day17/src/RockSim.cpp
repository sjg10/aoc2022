#include <cassert>
#include <memory>
#include <iostream>
#include "RockSim.h"


Rock::Rock(unsigned int floor_level, unsigned int type) {
    switch (type) {
        case 0:
            m_position.push_back(std::make_pair(2,floor_level + 3));
            m_position.push_back(std::make_pair(3,floor_level + 3));
            m_position.push_back(std::make_pair(4,floor_level + 3));
            m_position.push_back(std::make_pair(5,floor_level + 3));
            break;
        case 1:
            m_position.push_back(std::make_pair(3,floor_level + 3));
            m_position.push_back(std::make_pair(2,floor_level + 4));
            m_position.push_back(std::make_pair(3,floor_level + 4));
            m_position.push_back(std::make_pair(4,floor_level + 4));
            m_position.push_back(std::make_pair(3,floor_level + 5));
            break;
        case 2:
            m_position.push_back(std::make_pair(2,floor_level + 3));
            m_position.push_back(std::make_pair(3,floor_level + 3));
            m_position.push_back(std::make_pair(4,floor_level + 3));
            m_position.push_back(std::make_pair(4,floor_level + 4));
            m_position.push_back(std::make_pair(4,floor_level + 5));
            break;
        case 3:
            m_position.push_back(std::make_pair(2,floor_level + 3));
            m_position.push_back(std::make_pair(2,floor_level + 4));
            m_position.push_back(std::make_pair(2,floor_level + 5));
            m_position.push_back(std::make_pair(2,floor_level + 6));
            break;
        case 4:
            m_position.push_back(std::make_pair(2,floor_level + 3));
            m_position.push_back(std::make_pair(3,floor_level + 3));
            m_position.push_back(std::make_pair(2,floor_level + 4));
            m_position.push_back(std::make_pair(3,floor_level + 4));
            break;
        default:
            assert(false);
            break;
    }
}


bool Rock::move(RockSim &sim, Direction const &direction) {
    auto new_position = m_position;
    switch (direction) {
        case Direction::LEFT:
            for (unsigned int i = 0; i < new_position.size(); i++) {
                new_position[i].first--;
                if (m_position[i].first == 0 || /* Hit left */
                    (sim.m_map.size() > new_position[i].second && sim.m_map[new_position[i].second][new_position[i].first])) {
                        return false;
                }
            }
            break;
        case Direction::RIGHT:
            for (unsigned int i = 0; i < new_position.size(); i++) {
                new_position[i].first++;
                if (m_position[i].first == (RockSim::WIDTH - 1) || /* Hit right */
                    (sim.m_map.size() > new_position[i].second && sim.m_map[new_position[i].second][new_position[i].first])) {
                        return false;
                }
            }
            break;
        case Direction::DOWN:
            for (unsigned int i = 0; i < new_position.size(); i++) {
                new_position[i].second--;
                if (m_position[i].second == 0 || /* Hit floor */
                    (sim.m_map.size() > new_position[i].second && sim.m_map[new_position[i].second][new_position[i].first])) {
                        settleRock(sim);
                        return false;
                }
            }
            break;
    }
    m_position = new_position;
    return true;
}

void Rock::settleRock(RockSim &sim) {
    for (auto const &p : m_position) {
        while (p.second + 1 > sim.m_map.size()) {
            sim.m_map.push_back(std::vector<bool>(RockSim::WIDTH, false));
        }
        sim.m_map[p.second][p.first] = true;
    }
}


RockSim::RockSim(std::string &jetpattern) {
    for(auto const &c: jetpattern) {
        m_jetpattern.push_back((c== '<') ? Direction::LEFT : Direction::RIGHT);
    }
}

bool RockSim::adjustFloor() {
    /*const int maxheight = 38;
    if(m_map.size() > maxheight) { // found heuristically
        unsigned int floors = m_map.size() - maxheight;
        m_floor_offset += floors;
        m_map.erase(m_map.begin(), m_map.begin() + floors);
    }*//*
    auto newfloor = std::vector<bool>(WIDTH, true);
    auto f = std::find(m_map.rbegin(), m_map.rend(), newfloor);
    if (f != m_map.rend()) {
        //new floor
        unsigned int removed_floors = (m_map.rend() - f);
        m_floor_offset += removed_floors;
        m_map.erase(m_map.begin(), m_map.begin() + removed_floors);
        //std::cout << m_next_rock_type << " " << m_jetlevel << std::endl;
        if(m_next_rock_type == 0 && m_jetlevel == 0) { std::cout << "RECURSE " << m_floor_offset << std::endl; return true;}
    }*/
    return false;
}

void RockSim::run(unsigned long int rocks) {
    for (unsigned long int i =0; i < rocks; i++) {
        std::unique_ptr<Rock> rock = std::make_unique<Rock>(m_map.size(), m_next_rock_type);
        m_next_rock_type++;
        m_next_rock_type %= 5;
        bool fell = true;
        do {
            rock->move(*this, m_jetpattern[m_jetlevel]);
            m_jetlevel++;
            m_jetlevel %= m_jetpattern.size();
            fell = rock->move(*this, Direction::DOWN);
        } while(fell);
    }
}

std::ostream& operator<<(std::ostream& os, const RockSim& rs) {
    for(auto itr = rs.m_map.rbegin(); itr != rs.m_map.rend(); itr++) {
        os <<"|";
        for(auto const &x : *itr) {
            if (x) os <<"#";
            else os << ".";
        }
        os <<"|";
        os << std::endl;
    }
    os << "+-------+" << std::endl;
    return os;
}