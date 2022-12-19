#pragma once
#include "Day.h"
#include <list>

class Day18 : public Day {
    public:
        Day18(const std::string &input_filename) : Day(input_filename) {}
    private:
        std::vector<std::string> run(std::ifstream &input) override;
};