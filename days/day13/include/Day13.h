#pragma once
#include "Day.h"
#include <list>

class Day13 : public Day {
    public:
        Day13(const std::string &input_filename) : Day(input_filename) {}
        /** Get the pair and total sort scores */
        static std::pair<unsigned int, unsigned int> getSortScores(std::istream &input);
    private:
        std::vector<std::string> run(std::ifstream &input) override;
};