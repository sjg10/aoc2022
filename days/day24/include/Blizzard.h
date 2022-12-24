#pragma once
#include <vector>
#include <set>
#include <memory>
#include <sstream>

using Point = std::pair<unsigned int, unsigned int>;

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Blizzards {
public:
    Blizzards() {};
    void addBlizzard(unsigned int x, unsigned int y, Direction d);
    void setBounds(unsigned int width, unsigned int height);
    std::vector<std::tuple<int, unsigned int, unsigned int>> getMoves(int xin, unsigned int y, unsigned int d);
private:
    unsigned int m_width;
    unsigned int m_height;
    std::vector<std::vector<unsigned int>> upgoingcolumns =       std::vector<std::vector<unsigned int>>(200, std::vector<unsigned int>());
    std::vector<std::vector<unsigned int>> downgoingcolumns =    std::vector<std::vector<unsigned int>>(200, std::vector<unsigned int>());
    std::vector<std::vector<unsigned int>> leftgoingrows =       std::vector<std::vector<unsigned int>>(200, std::vector<unsigned int>());
    std::vector<std::vector<unsigned int>> rightgoingrows =      std::vector<std::vector<unsigned int>>(200, std::vector<unsigned int>());
};

class BlizzardMap {
public:
    BlizzardMap(std::istream &in);
    std::pair<unsigned int, unsigned int> getPathLengths();
private:
std::pair<unsigned int, unsigned int> getShortestPath(bool start_to_finish, unsigned int startd);
    std::unique_ptr<Blizzards> blizzards;
    unsigned int wrap;
    unsigned int m_width;
    unsigned int m_height;
};