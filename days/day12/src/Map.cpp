#include "Map.h"
#include <list>
#include <cassert>

Map::Map(std::istream &input) {
    for(std::string readline; std::getline(input,readline);) {
        addRow(readline);
    }

}

void Map::addRow(std::string input) {
    width = input.size();
    for (unsigned int x = 0; x < width; x++){
        if (input[x] == 'S') {
            start = points.size();
            points.push_back({x, height, 0});
        }
        else if  (input[x] == 'E') {
            end = points.size();
            points.push_back({x, height, 25});
        }
        else  {
            points.push_back({x, height, input[x] - 'a'});
        }
    }
    height++;
}

unsigned int Map::getShortestPathForward() {
    std::vector<bool> visited(points.size(), false);
    std::vector<unsigned int> d(points.size(), 0);
    std::list<int> queue;

    visited[start] = true;
    queue.push_back(start);
    unsigned int s = 0;

    while(!queue.empty()) {
        s = queue.front();
        queue.pop_front();
        Point p = points[s];
        if(p.x > 0) { // left
            unsigned int p2 = s - 1;
            if(!visited[p2]) {
                Point u = points[p2];
                if (u.z <= (p.z + 1)) {
                    d[p2] = d[s] + 1;
                    if (p2 == end) {
                        return d[p2];
                    }
                    visited[p2] = true;
                    queue.push_back(p2);
                }
            }
        } 
        if(p.x < width - 1) { // right
            unsigned int p2 = s + 1;
            if(!visited[p2]) {
                Point u = points[p2];
                if (u.z <= (p.z + 1)) {
                    d[p2] = d[s] + 1;
                    if (p2 == end) {
                        return d[p2];
                    }
                    visited[p2] = true;
                    queue.push_back(p2);
                }
            }
        }
        if(p.y > 0) {
            unsigned int p2 = s - width;
            if(!visited[p2]) { //up
                Point u = points[p2];
                if (u.z <= (p.z + 1)) {
                    d[p2] = d[s] + 1;
                    if (p2 == end) {
                        return d[p2];
                    }
                    visited[p2] = true;
                    queue.push_back(p2);
                }
            }
        }
        if(p.y < height - 1) { // down
            unsigned int p2 = s + width;
            if(!visited[p2]) {
                Point u = points[p2];
                if (u.z <= (p.z + 1)) {
                    d[p2] = d[s] + 1;
                    if (p2 == end) {
                        return d[p2];
                    }
                    visited[p2] = true;
                    queue.push_back(p2);
                }
            }
        }
    }
    assert(false); // no path was found!
    return 0;
}


unsigned int Map::getShortestPathBackward() {
    std::vector<bool> visited(points.size(), false);
    std::vector<unsigned int> d(points.size(), 0);
    std::list<int> queue;

    visited[end] = true;
    queue.push_back(end);
    unsigned int s = 0;

    while(!queue.empty()) {
        s = queue.front();
        queue.pop_front();
        Point p = points[s];
        if(p.x > 0) { // left
            unsigned int p2 = s - 1;
            if(!visited[p2]) {
                Point u = points[p2];
                if (u.z >= p.z  - 1) {
                    d[p2] = d[s] + 1;
                    if (u.z == 0) {
                        return d[p2];
                    }
                    visited[p2] = true;
                    queue.push_back(p2);
                }
            }
        } 
        if(p.x < width - 1) { // right
            unsigned int p2 = s + 1;
            if(!visited[p2]) {
                Point u = points[p2];
                if (u.z >= p.z  - 1) {
                    d[p2] = d[s] + 1;
                    if (u.z == 0) {
                        return d[p2];
                    }
                    visited[p2] = true;
                    queue.push_back(p2);
                }
            }
        }
        if(p.y > 0) {
            unsigned int p2 = s - width;
            if(!visited[p2]) { //up
                Point u = points[p2];
                if (u.z >= p.z  - 1) {
                    d[p2] = d[s] + 1;
                    if (u.z == 0) {
                        return d[p2];
                    }
                    visited[p2] = true;
                    queue.push_back(p2);
                }
            }
        }
        if(p.y < height - 1) { // down
            unsigned int p2 = s + width;
            if(!visited[p2]) {
                Point u = points[p2];
                if (u.z >= p.z  - 1) {
                    d[p2] = d[s] + 1;
                    if (u.z == 0) {
                        return d[p2];
                    }
                    visited[p2] = true;
                    queue.push_back(p2);
                }
            }
        }
    }
    assert(false); // no path was found!
    return 0;
}

