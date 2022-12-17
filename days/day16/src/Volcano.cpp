#include "Volcano.h"
#include <regex>
#include <cassert>
#include <sstream>
#include <list>
#include <iostream>
#include <limits>
#include <future>


void Volcano::addRoom(std::string &in) {
    //Read instructions
    const std::regex re("Valve (..) has flow rate=(\\d*); tunnels? leads? to valves? (.*)");
    std::smatch m;
    std::regex_match(in, m, re);
    assert(m.size() == 4);
    std::string name = m.str(1);
    m_valve_release[name] = std::stoul(m.str(2));
    std::stringstream ss(m.str(3));
    m_neighbours[name] = std::vector<std::string>();
    size_t last = 0;
    for(size_t x = m.str(3).find(", "); x != std::string::npos; x = m.str(3).find(", ", x + 1)) {
        m_neighbours[name].push_back(m.str(3).substr(last, x - last));
        last = x + 2;
    }
    m_neighbours[name].push_back(m.str(3).substr(last));
    if (name == "AA" || m_valve_release[name] > 0) {
        m_important_rooms.insert(name);
    }
}



void Volcano::getShortestPaths(std::string start_point) {
    std::map<std::string, bool> visited;
    std::map<std::string, unsigned int> d;
    for(auto const &x: m_neighbours) {
        visited[x.first] = false;
        d[x.first] = 0;
    } 
    std::list<std::string> queue;

    visited[start_point] = true;
    queue.push_back(start_point);
    std::string s = "";

    while(!queue.empty()) {
        s = queue.front();
        queue.pop_front();
        for(auto const n : m_neighbours[s]) {
            if(!visited[n]) {
                d[n] = d[s] + 1;
                visited[n] = true;
                queue.push_back(n);
            }
        }
    }
    m_distances[start_point] = std::map<std::string, unsigned int>();
    for(auto const &x: m_important_rooms) {
        m_distances[start_point][x] = d[x];
    } 
}

unsigned int Volcano::getBestRoute(std::string first_room, std::set<std::string> rooms, unsigned int score, unsigned int t) {
    rooms.erase(first_room);
    if (rooms.empty()) {
        return score;
    }
    unsigned int max = score;
    for(auto const &room : rooms) {
        //if(first_room == "AA") {std::cout << room << std::endl;}
        unsigned int tdiff = (m_distances[first_room][room] + 1);
        if (tdiff > t) {continue;}
        unsigned int scorediff = (t - tdiff) * m_valve_release[room];
        unsigned int res = getBestRoute(room, rooms, score + scorediff, t-tdiff);
        if (res > max) { max = res;}
    }
    return max;
}

unsigned int Volcano::getBestElephantPressure() {
    std::set<std::string> rooms_to_visit = m_important_rooms;
    rooms_to_visit.erase("AA");
    unsigned int max = 0;
    
    // We the optimal strategy has both you and elephant visit same number of valves (+/-1)
    std::vector<std::string> ordered_rooms(rooms_to_visit.begin(), rooms_to_visit.end());
    std::vector<bool> include_my_room(rooms_to_visit.size(), false);
    std::fill(include_my_room.end() - rooms_to_visit.size() / 2, include_my_room.end(), true);

    const unsigned int threads = std::thread::hardware_concurrency();

    auto runner = [&] (std::vector<bool> v) {
        std::set<std::string> my_rooms = {"AA"};
        std::set<std::string> elephant_rooms = {"AA"};
        unsigned int j = 0;
        for(auto room = rooms_to_visit.cbegin(); room != rooms_to_visit.cend(); room++, j++) {
            if (v[j]) {
                my_rooms.insert(*room);
            }
            else {
                elephant_rooms.insert(*room);
            }
        }
        unsigned int res1 = getBestRoute("AA", my_rooms, 0, 26);
        unsigned int res2 = getBestRoute("AA", elephant_rooms, 0, 26);
        return res1 + res2;
    };

    bool cont = true;
    do {
        std::vector<std::future<unsigned int>> futures;
        for(long int ystep = 0; ystep < threads && cont; ystep++) {
            futures.emplace_back(std::async(std::launch::async,
                                    runner, include_my_room));
            cont = std::next_permutation(include_my_room.begin(), include_my_room.end());
        }
        for (auto &f : futures) {
            auto res = f.get();
            if (res > max) {max = res;}
        }
    } while (cont);
    return max;
}

unsigned int Volcano::getBestPressure() {
    for(auto const &x: m_important_rooms) {
        getShortestPaths(x);
    }
    return getBestRoute("AA", m_important_rooms, 0, 30);
}
