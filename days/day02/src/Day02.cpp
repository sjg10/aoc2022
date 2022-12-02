#include <iostream>
#include <string>
#include "Day02.h"


std::vector<std::string> Day02::run(std::ifstream &input) {
    std::vector<std::string> out;
    auto score = scoreRPS(input);
    out.push_back(std::to_string(score.first));
    out.push_back(std::to_string(score.second));
    return out;
}

const std::map<std::string, int> Day02::score_map1 = {
    {"A X", 3 + 1},
    {"A Y", 6 + 2},
    {"A Z", 0 + 3},
    {"B X", 0 + 1},
    {"B Y", 3 + 2},
    {"B Z", 6 + 3},
    {"C X", 6 + 1},
    {"C Y", 0 + 2},
    {"C Z", 3 + 3},
};

const std::map<std::string, int> Day02::score_map2 = {
    {"A X", 0 + 3},
    {"A Y", 3 + 1},
    {"A Z", 6 + 2},
    {"B X", 0 + 1},
    {"B Y", 3 + 2},
    {"B Z", 6 + 3},
    {"C X", 0 + 2},
    {"C Y", 3 + 3},
    {"C Z", 6 + 1},
};


std::pair<unsigned int,unsigned int> Day02::scoreRPS(std::istream &input) {
    unsigned int score1 = 0, score2 = 0;
    for(std::string read_string; std::getline(input, read_string);) {
        score1 += score_map1.at(read_string);
        score2 += score_map2.at(read_string);
    }
    return {score1, score2};
}