#include <iostream>
#include <string>
#include <unordered_set>
#include "Day06.h"


std::vector<std::string> Day06::run(std::ifstream &input) {
    std::vector<std::string> out;
    std::string read_line;
    getline(input, read_line);
    out.push_back(std::to_string(getPreambleStart(read_line)));
    out.push_back(std::to_string(getPreambleStart(read_line, 14)));
    return out;
}

unsigned int Day06::getPreambleStart(const std::string &input, unsigned int length) {
    unsigned int i;
    for (i = 0; i < input.size() - length; i++) {
        std::unordered_set<char> preamble(input.begin() + i, input.begin() + i + length);
        if(preamble.size() == length) { break;}
    }
    return i + length;
}