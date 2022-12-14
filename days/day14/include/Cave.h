#pragma once
#include <string>
#include <vector>
#include <limits>
#include <unordered_map>

using Point = std::pair<unsigned int, unsigned int>;

// Simple hash so Point can be a key in unordered_map, works iff p.second < 1000;
namespace std
{
    template<>
    struct hash<Point>
    {
        size_t operator()(Point const& p) const
        {
            return (p.first * 1000) + p.second;
        }
    };
}

class Cave {
public:
    Cave() {}
    void addLine(std::string &in);
    bool addSand(); // returns true if sand settled
    unsigned int getSandCount() const { return m_sand_count;}
    unsigned int getSandCountFloored() const { return m_sand_count_floor;}
    enum Material {
        EMPTY = 0,
        ROCK = 1,
        SAND = 2
    };
private:
    // Add a line from last_x, last_y to new x,y, return new coord.
    void addLinePrivate(unsigned int last_x, unsigned int last_y, unsigned int x, unsigned int y);
    void updateRange(unsigned int smallx, unsigned int bigx, unsigned int smally, unsigned int bigy );
    unsigned int  m_sand_count = 0;
    unsigned int  m_sand_count_floor = 0;
    std::unordered_map<Point,Material> m_map; // TODO: try unordered_map too
    std::vector<std::pair<unsigned int, unsigned int>> m_rock_queue;
    unsigned int min_x = std::numeric_limits<unsigned int>::max();
    unsigned int max_x = 0;
    unsigned int min_y = std::numeric_limits<unsigned int>::max();
    unsigned int max_y = 0;
    unsigned int m_height;
    unsigned int m_width;
    bool m_sand_hit_floor = false;
};