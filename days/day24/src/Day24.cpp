#include <iostream>
#include <string>
#include <memory>
#include "Day24.h"
#include "Blizzard.h"


std::vector<std::string> Day24::run(std::ifstream &input) {
    std::vector<std::string> out;
    auto b = std::make_unique<BlizzardMap>(input);
    auto res = b->getPathLengths();
    out.push_back(std::to_string(res.first));
    out.push_back(std::to_string(res.second));
    return out;
}