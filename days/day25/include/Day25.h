#pragma once
#include "Day.h"
#include <list>
#include <string>

class Day25 : public Day {
    public:
        Day25(const std::string &input_filename) : Day(input_filename) {}
        static long int snafuToInt(std::string in);
        static std::string IntToSnafu(long int in);
    private:
        std::vector<std::string> run(std::ifstream &input) override;
};