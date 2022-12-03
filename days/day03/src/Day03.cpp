#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <memory>
#include "Day03.h"
#include "Rucksacks.h"


std::vector<std::string> Day03::run(std::ifstream &input) {
    std::vector<std::string> out;
    auto r = std::make_unique<Rucksacks>(input);
    auto v1 = r->getIntersects();
    auto v2 = r->getBadges();
    out.push_back(std::to_string(std::accumulate(v1.begin(), v1.end(), 0)));
    out.push_back(std::to_string(std::accumulate(v2.begin(), v2.end(), 0)));
    return out;
}
