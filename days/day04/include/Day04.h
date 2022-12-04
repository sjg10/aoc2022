#pragma once
#include "Day.h"
#include <list>

class Day04 : public Day {
    public:
        Day04(const std::string &input_filename) : Day(input_filename) {}
        /* Get the count of each type of range overlap */
        static std::pair<unsigned int,unsigned int>  getOverlaps(std::istream &input);
    private:
        std::vector<std::string> run(std::ifstream &input) override;
};