#include <iostream>
#include <string>
#include <numeric>
#include <memory>
#include "Day09.h"
#include "Rope.h"


std::vector<std::string> Day09::run(std::ifstream &input) {
    std::vector<std::string> out;
    std::string read_line;

    auto r = std::make_unique<Rope>(2);
    auto r2 = std::make_unique<Rope>(10);
    for(std::string readline; std::getline(input,readline);) {
        r->moveHead(readline);
        r2->moveHead(readline);
    }
    out.push_back(std::to_string(r->getTailPositions()));
    out.push_back(std::to_string(r2->getTailPositions()));
    return out;
}