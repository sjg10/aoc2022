#pragma once
#include "Day.h"
#include <list>

class Day16 : public Day {
    public:
        Day16(const std::string &input_filename) : Day(input_filename) {}
    private:
        std::vector<std::string> run(std::ifstream &input) override;
};