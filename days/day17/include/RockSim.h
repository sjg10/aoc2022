#pragma once
#include <string>
#include <vector>
#include <deque>

enum Direction {
    LEFT,
    RIGHT,
    DOWN,
};
using Point = std::pair<unsigned int, unsigned int>;

class RockSim;

class Rock {
public:
    Rock(unsigned int floor_level, unsigned int type);
    // tries to move the rock, reutrns success if rock cant fall, inserted into sim
    bool move(RockSim &sim, Direction const &direction); 
private:
    void settleRock(RockSim &sim);
    std::vector<Point> m_position;
};


class RockSim {
public:
    RockSim(std::string &jetpattern);
    void run(unsigned long int rocks);
    unsigned long int getTowerHeight() { return m_map.size() + m_floor_offset;}
    friend Rock;
    friend std::ostream& operator<<(std::ostream& os, const RockSim& rs);
private:
    unsigned long int m_total_steps_run = 0;
    unsigned long int m_floor_offset = 0;
    static const unsigned int WIDTH = 7;
    std::deque<std::vector<bool>> m_map;
    std::vector<Direction> m_jetpattern;
    unsigned int m_next_rock_type = 0;
    unsigned int m_jetlevel = 0;

    // if recursion detected, true, and the following is all filled in *hacky*
    bool adjustFloor();
    std::vector<std::pair<unsigned int, unsigned int>> m_detected_floor_level;
    std::vector<unsigned int> m_floor_level_heights;
    std::vector<unsigned int> m_floor_level_rock_counts;
    bool m_floor_repeat_found = false;
    unsigned int rocks_fallen_reset_1;
    unsigned int rocks_fallen_reset_1_floors;
    unsigned int rocks_fallen_reset_2;
    unsigned int rocks_fallen_reset_2_floors;
};