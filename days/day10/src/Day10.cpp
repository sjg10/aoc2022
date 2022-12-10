#include <iostream>
#include <string>
#include <numeric>
#include <memory>
#include "Day10.h"
#include "CPU.h"


std::vector<std::string> Day10::run(std::ifstream &input) {
    std::vector<std::string> out;
    auto c = std::make_unique<CPU>();
    for (std::string read_line; std::getline(input, read_line);) {
        c->parseCommand(read_line);
    }
    out.push_back(std::to_string(c->getSignalStrengthTotal()));
    out.push_back("\n" + c->drawScreen());
    return out;
}