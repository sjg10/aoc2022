#pragma once
#include "Day.h"

class Day01 : public Day {
    public:
        Day01(const std::string &input_filename) : Day(input_filename) {}
    private:
        std::vector<std::string> run(std::ifstream &input) override;
};