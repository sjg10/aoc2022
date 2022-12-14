#include <iostream>
#include <string>
#include <memory>
#include "Day14.h"
#include "Cave.h"


std::vector<std::string> Day14::run(std::ifstream &input) {
    std::vector<std::string> out;
    auto c = std::make_unique<Cave>();
    for (std::string read_line; std::getline(input, read_line);) {
        c->addLine(read_line);
    }
    bool cont = true;
    do {
        cont = c->addSand();
    } while(cont);
    out.push_back(std::to_string(c->getSandCount()));
    out.push_back(std::to_string(c->getSandCountFloored()));
    return out;
}