#pragma once
#include <string>
#include <vector>
#include <istream>
#include <functional>

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
    unsigned int getShortestPath(unsigned int start_point_idx, std::function<bool(int, int)> height_test, std::function<bool(unsigned int)>  end_test);
    void addRow(std::string input);
    std::vector<Point> points;
    unsigned int start; //index of start into points
    unsigned int end; // index of end into points
    unsigned int width = 0;
    unsigned int height = 0;
};