#pragma once
#include "Day.h"
#include <list>

class Day17 : public Day {
    public:
        Day17(const std::string &input_filename) : Day(input_filename) {}
    private:
        std::vector<std::string> run(std::ifstream &input) override;
};