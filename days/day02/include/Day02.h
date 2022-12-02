#pragma once
#include "Day.h"
#include <map>

class Day02 : public Day {
    public:
        Day02(const std::string &input_filename) : Day(input_filename) {}
        /** Scores a rock paper scissors game interpretation 1 and 2 as a pair */
        static std::pair<unsigned int, unsigned int> scoreRPS(std::istream &input);
    private:
        std::vector<std::string> run(std::ifstream &input) override;
        /* Maps used for scoring each strategy */
        static const std::map<std::string, int> score_map1;
        static const std::map<std::string, int> score_map2;
};