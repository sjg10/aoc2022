#include <iostream>
#include <string>
#include "Day01.h"


std::vector<std::string> Day01::run(std::ifstream &input) {
    std::vector<std::string> out;
    out.push_back("Hello");
    input.clear(); input.seekg(0);
    out.push_back("world");
    return out;
}
