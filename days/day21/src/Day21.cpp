#include <iostream>
#include <string>
#include <memory>
#include "Day21.h"
#include "MonkeyMaths.h"


std::vector<std::string> Day21::run(std::ifstream &input) {
    std::vector<std::string> out;
    auto m = std::make_unique<MonkeyMaths>(input);
    out.push_back(std::to_string(m->getRootScore()));
    out.push_back(std::to_string(m->getHumanScore()));
    return out;
}