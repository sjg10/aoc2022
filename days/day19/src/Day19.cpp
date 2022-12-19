#include <iostream>
#include <string>
#include <memory>
#include "Day19.h"
#include "GeodeFactory.h"


std::vector<std::string> Day19::run(std::ifstream &input) {
    std::vector<std::string> out;
    auto gf = std::make_unique<Factory>();
    for(std::string readline; std::getline(input, readline);) {
        gf->loadBlueprint(readline);
    }
    out.push_back(std::to_string(gf->getTotalScore()));
    out.push_back(std::to_string(gf->getTotalScore2()));
    return out;
}