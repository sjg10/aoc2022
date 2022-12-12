#pragma once
#include <string>
#include <vector>
#include <istream>

struct Point {
    unsigned int x;
    unsigned int y;
    int z;
};

class Map {
public:
    Map(std::istream &input);
    unsigned int getShortestPathForward();
    unsigned int getShortestPathBackward();
private:
    void addRow(std::string input);
    std::vector<Point> points;
    unsigned int start; //index of start into points
    unsigned int end; // index of end into points
    unsigned int width = 0;
    unsigned int height = 0;
};