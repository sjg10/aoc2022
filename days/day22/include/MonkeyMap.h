#pragma once
#include <sstream>
#include <vector>


enum Location {
    OPEN,
    EMPTY,
    ROCK,
};

enum Direction {
    RIGHT=0,
    DOWN=1,
    LEFT=2,
    UP=3,
};

class MonkeyMap {
public:
    MonkeyMap(std::istream &in);
    unsigned int getScore(unsigned int cube_face_size = 0);
private:
    void loadLine(std::string const &line);
    void wrapDown(unsigned int &row, unsigned int &col, Direction &dir, unsigned int cube_face_size);
    void wrapUp(unsigned int &row, unsigned int &col, Direction &dir, unsigned int cube_face_size);
    void wrapLeft(unsigned int &row, unsigned int &col, Direction &dir, unsigned int cube_face_size);
    void wrapRight(unsigned int &row, unsigned int &col, Direction &dir, unsigned int cube_face_size);
    std::vector<std::vector<Location>> m_map;
    std::vector<unsigned int> m_rowstart;
    std::vector<unsigned int> m_rowend;
    std::vector<unsigned int> m_colstart;
    std::vector<unsigned int> m_colend;
    unsigned int m_width = 0;
    std::vector<Direction> m_turns;
    std::vector<unsigned int> m_distances;
};