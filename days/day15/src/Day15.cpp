#include <iostream>
#include <string>
#include <numeric>
#include <memory>
#include "Day15.h"
#include "BeaconMap.h"


std::vector<std::string> Day15::run(std::ifstream &input) {
    std::vector<std::string> out;
    auto b = std::make_unique<BeaconMap>(input);
    out.push_back(std::to_string(b->getRowPositions(2000000)));
    out.push_back(std::to_string(b->findBeacon(4000000)));
    return out;
}