#pragma once
#include "Day.h"
#include <vector>

struct Tree {
    unsigned int val;
    unsigned int scenic_left;
    unsigned int scenic_right;
    unsigned int scenic_up;
    unsigned int scenic_down;
    bool detected_visible = false;
};

class Day08 : public Day {
    public:
        Day08(const std::string &input_filename) : Day(input_filename) {}
        /** Create tree structure from input */
        static std::vector<std::vector<Tree>> parseInput(std::istream &input);
        /** Parse a tree structure for visible count, max scenic score */
        static std::pair<unsigned int,unsigned int> visibleCount(std::vector<std::vector<Tree>> &forest);
    private:
        std::vector<std::string> run(std::ifstream &input) override;
};