#include "Cave.h"
#include <cassert>
#include <iostream>
/*
#pragma once
#include <string>
#include <vector>

class Cave {
public:
    Cave() {}
    void addLine(std::string &in);
    void finaliseLoad();
    void addSand();
    unsigned int getSandCount() const { return m_sand_count;}
    enum Point {
        EMPTY = 0,
        ROCK = 1,
        SAND = 2
    };
private:
    unsigned int  m_sand_count;
    std::vector<Point> m_map;
    std::vector<std::pair<unsigned int, unsigned int>> m_rock_queue;
    unsigned int min_x;
    unsigned int max_x;
    unsigned int min_y;
    unsigned int max_y;
};
*/
void Cave::updateRange(unsigned int smallx, unsigned int bigx, unsigned int smally, unsigned int bigy ) {
    if(bigx > max_x) { max_x = bigx;}
    if(smallx < min_x) { min_x = smallx;}
    if(bigy > max_y) { max_y = bigy;}
    if(smally < min_y) { min_y = smally;}
}

void Cave::addLinePrivate(unsigned int last_x, unsigned int last_y, unsigned int x, unsigned int y) {
    if (y == last_y) {
        if (x < last_x) {
            for(unsigned int xoffset = 0; xoffset <= (last_x - x); xoffset++) {
                m_map[Point({x + xoffset, y})] = Material::ROCK;
            }
            updateRange(x, last_x, y, y);
        }
        else {
            for(unsigned int xoffset = 0; xoffset <= (x - last_x); xoffset++) {
                m_map[Point({last_x + xoffset, y})] = Material::ROCK;
            }
            updateRange(last_x, x, y, y);
        }
    }
    else if (x == last_x) {
        if (y < last_y) {
            for(unsigned int yoffset = 0; yoffset <= (last_y - y); yoffset++) {
                m_map[Point({x, y + yoffset})] = Material::ROCK;
            }
            updateRange(x, x, y, last_y);
        }
        else {
            for(unsigned int yoffset = 0; yoffset <= (y - last_y); yoffset++) {
                m_map[Point({x, last_y + yoffset})] = Material::ROCK;
            }
            updateRange(x, x, last_y, y);
        }
    }
    else {
        assert(false);
    }
}

void Cave::addLine(std::string &in) {
    size_t last = 0;
    unsigned int last_x = 0;
    unsigned int last_y = 0;
    for(size_t ptr = in.find(" -> "); ptr != std::string::npos; ptr = in.find(" -> ", ptr + 1)) {
        std::string coord = in.substr(last, ptr - last);
        auto c = coord.find(",");
        unsigned int x = std::stoul(coord.substr(0,c));
        unsigned int y = std::stoul(coord.substr(c + 1));
        if(last != 0) {addLinePrivate(last_x, last_y, x, y);}
        last = ptr + 4;
        last_x = x;
        last_y = y;
    }
    //final line
    std::string coord = in.substr(last);
    auto c = coord.find(",");
    unsigned int x = std::stoul(coord.substr(0,c));
    unsigned int y = std::stoul(coord.substr(c + 1));
    addLinePrivate(last_x, last_y, x, y);
}

bool Cave::addSand() {
    unsigned int y = 0;
    unsigned int x = 500;
    do {
        if (y == (max_y + 1)) { // hit the floor
            m_sand_hit_floor = true;
            m_sand_count_floor++;
            m_map[Point({x, y})] = Material::SAND;
            break;
        }
        else {
            if (m_map.find(Point({x, y + 1})) == m_map.end()) {
                y++;
            }
            else if (m_map.find(Point({x - 1, y + 1})) == m_map.end()) {
                x--;
                y++;
            }
            else if (m_map.find(Point({x + 1, y + 1})) == m_map.end()) {
                x++;
                y++;
            }
            else {
                if (!m_sand_hit_floor) {m_sand_count++;}
                m_sand_count_floor++;
                m_map[Point({x, y})] = Material::SAND;
                break;
            }
        }
    } while(true);
    /*std::cout << std::endl;
    std::cout << std::endl;
    for (unsigned int y1 = 0; y1 <= max_y + 1; y1++) {
        for (unsigned int x1 = min_x - 10; x1 <= max_x + 10; x1++) {
        auto p = m_map.find(Point({x1, y1}));
        if(p == m_map.end()) {std::cout << ".";}
        else if(p->second == Material::SAND) {std::cout << "o";}
        else if(p->second == Material::ROCK) {std::cout << "#";}
    }
    std::cout << std::endl;
    }*/
    

    return Point({x, y}) != Point({500, 0});
}
