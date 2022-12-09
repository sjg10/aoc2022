#pragma once
#include <vector>
#include <set>

using Point = std::pair<int, int>;

class Rope {
public:
    Rope(unsigned int knot_count) {knots = std::vector(knot_count, std::make_pair(0,0));};
    void moveHead(std::string input);
    unsigned int getTailPositions() {return tailPositions.size();};
private:
    void moveTails();
    std::set<Point> tailPositions = {{0,0}};
    std::vector<Point> knots;
};