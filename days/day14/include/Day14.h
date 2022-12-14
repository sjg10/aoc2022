#pragma once
#include "Day.h"
#include <list>

class Day14 : public Day {
    public:
        Day14(const std::string &input_filename) : Day(input_filename) {}
    private:
        std::vector<std::string> run(std::ifstream &input) override;
};