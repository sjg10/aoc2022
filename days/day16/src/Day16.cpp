#include <iostream>
#include <string>
#include <memory>
#include "Day16.h"
#include "Volcano.h"


std::vector<std::string> Day16::run(std::ifstream &input) {
    std::vector<std::string> out;
    auto v = std::make_unique<Volcano>();
    for (std::string read_line; std::getline(input, read_line);) {
        v->addRoom(read_line);
    }
    out.push_back(std::to_string(v->getBestPressure()));
    out.push_back(std::to_string(v->getBestElephantPressure()));
    return out;
}