#include <iostream>
#include <string>
#include <memory>
#include "Day18.h"
#include "CubeMap.h"

std::vector<std::string> Day18::run(std::ifstream &input) {
    std::vector<std::string> out;
    auto c = std::make_unique<CubeMap>();
    for(std::string readline; std::getline(input, readline);) {
        c->addPoint(readline);
    }
    out.push_back(std::to_string(c->getFaces()));
    out.push_back(std::to_string(c->getExteriorArea()));
    return out;
}