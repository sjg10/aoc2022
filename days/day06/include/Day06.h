#pragma once
#include "Day.h"

class Day06 : public Day {
    public:
        Day06(const std::string &input_filename) : Day(input_filename) {}
        /** Get the charachter offset following a non repeating preamble of given length */
        static unsigned int getPreambleStart(const std::string &input, unsigned int length = 4);
    private:
        std::vector<std::string> run(std::ifstream &input) override;
};