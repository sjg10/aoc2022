#include <iostream>
#include <string>
#include <memory>
#include "Day22.h"
#include "MonkeyMap.h"


std::vector<std::string> Day22::run(std::ifstream &input) {
    std::vector<std::string> out;
    auto m = std::make_unique<MonkeyMap>(input);
    out.push_back(std::to_string(m->getScore()));
    out.push_back(std::to_string(m->getScore(50)));
    return out;
}