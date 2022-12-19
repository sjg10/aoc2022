#include "CubeMap.h"
#include <regex>
#include <cassert>
#include <iostream>
#include <list>

void CubeMap::addFace(Face f) {
    if (m_int_faces.find(f) != m_int_faces.end()) {
        return;
    }
    else if (m_ext_faces.find(f) != m_ext_faces.end()) {
        m_ext_faces.erase(f);
        m_int_faces.insert(f);
    }
    else {
        m_ext_faces.insert(f);
    }
}

void CubeMap::addPoint(std::string &point) {
    const std::regex re("(\\d*),(\\d*),(\\d*)");
    std::smatch m;
    std::regex_match(point, m, re);
    assert(m.size() == 4);
    int x = std::stoul(m.str(1)) * 2; //scale by 2 so faces get odd coords
    int y = std::stoul(m.str(2)) * 2; //scale by 2 so faces get odd coords
    int z = std::stoul(m.str(3)) * 2; //scale by 2 so faces get odd coords
    m_points.insert(std::make_tuple(x / 2,y / 2,z / 2));
    addFace(std::make_tuple(x + 1,y,z));
    addFace(std::make_tuple(x - 1,y,z));
    addFace(std::make_tuple(x,y + 1,z));
    addFace(std::make_tuple(x,y - 1,z));
    addFace(std::make_tuple(x,y,z + 1));
    addFace(std::make_tuple(x,y,z - 1));
}


// FLood fill
unsigned int CubeMap::getExteriorArea() {
    unsigned int f = 0;
    std::set<Cube> visited;
    int max_x = std::numeric_limits<int>::min(), max_y = std::numeric_limits<int>::min(), max_z = std::numeric_limits<int>::min();
    int min_x = std::numeric_limits<int>::max(), min_y = std::numeric_limits<int>::max(), min_z = std::numeric_limits<int>::max();
    for(auto const &p: m_points) {
        int x = std::get<0>(p);
        int y = std::get<1>(p);
        int z = std::get<2>(p);
        if(x > max_x) {max_x = x;}
        if(y > max_y) {max_y = y;}
        if(z > max_z) {max_z = z;}
        if(x < min_x) {min_x = x;}
        if(y < min_y) {min_y = y;}
        if(z < min_z) {min_z = z;}
    }
    min_x--; min_y--; min_z--;
    max_x++; max_y++; max_z++;


    std::list<Cube> queue;
    Cube start = std::make_tuple(min_x, min_y, min_z);
    queue.push_back(start);
    visited.insert(start);
    auto parse_next = [&](Cube next) {
        if(m_points.find(next) != m_points.end()) {
            f++;
        } else if (visited.find(next) == visited.end()) {
            visited.insert(next); queue.push_back(next);
        }
    };

    while(!queue.empty()) {
        Cube c = queue.front(); queue.pop_front();
        int x = std::get<0>(c);
        int y = std::get<1>(c);
        int z = std::get<2>(c);
        Cube next;
        if (x > min_x) {
            next = std::make_tuple(x - 1, y,z);
            parse_next(next);
        }
        if (x < max_x) {
            next = std::make_tuple(x + 1, y,z);
            parse_next(next);
        }
        if (y > min_y) {
            next = std::make_tuple(x, y - 1,z);
            parse_next(next);
        }
        if (y < max_y) {
            next = std::make_tuple(x, y + 1,z);
            parse_next(next);
        }
        if (z > min_z) {
            next = std::make_tuple(x, y, z - 1);
            parse_next(next);
        }
        if (z < max_z) {
            next = std::make_tuple(x, y, z + 1);
            parse_next(next);
        }
    }
    return f;
}
