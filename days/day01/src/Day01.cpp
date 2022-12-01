#include <iostream>
#include "Day01.h"


std::vector<std::string> Day01::run(std::ifstream &input) {
    std::vector<std::string> out;
    out.push_back(std::to_string(input));
    input.clear(); input.seekg(0);
    out.push_back(std::to_string(input));
    return out;
}
