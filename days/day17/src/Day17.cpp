#include <iostream>
#include <string>
#include <memory>
#include "Day17.h"
#include "RockSim.h"


std::vector<std::string> Day17::run(std::ifstream &input) {
    std::vector<std::string> out;
    std::string jetline;
    std::getline(input, jetline);
    auto s = std::make_unique<RockSim>(jetline);
    s->run(2022);
    out.push_back(std::to_string(s->getTowerHeight()));
    s->run(1000000000000 - 2022);
    out.push_back(std::to_string(s->getTowerHeight()));
    return out;
}