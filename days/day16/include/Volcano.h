#pragma once
#include <string>
#include <map>
#include <vector>
#include <set>

class Volcano {
public:
    Volcano() {}
    void addRoom(std::string &in);
    unsigned int getBestPressure();
    unsigned int getBestElephantPressure();
private:
    void getShortestPaths(std::string start_point);
    unsigned int getBestRoute(std::string first_room, std::set<std::string> rooms, unsigned int score, unsigned int t);
    std::map<std::string, std::vector<std::string>> m_neighbours;
    std::map<std::string, unsigned int> m_valve_release;
    std::set<std::string> m_important_rooms;
    // map starting room and non zero rooms to each other with shortest distances
    std::map<std::string, std::map<std::string, unsigned int>> m_distances;

};