#pragma once
#include "Day.h"
#include <list>

class Day01 : public Day {
    public:
        Day01(const std::string &input_filename) : Day(input_filename) {}
        /** Return a list of (elf index, calories) of the top elves. */
        static std::list<std::pair<unsigned int,unsigned int>> getMaxElf(std::istream &input, unsigned int elves=1);
    private:
        std::vector<std::string> run(std::ifstream &input) override;
};