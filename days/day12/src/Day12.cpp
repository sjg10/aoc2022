#include <iostream>
#include <string>
#include <numeric>
#include <memory>
#include "Day12.h"
#include "Map.h"


std::vector<std::string> Day12::run(std::ifstream &input) {
    std::vector<std::string> out;
    auto m = std::make_unique<Map>(input);
    out.push_back(std::to_string(m->getShortestPathForward()));
    out.push_back(std::to_string(m->getShortestPathBackward()));
    return out;
}