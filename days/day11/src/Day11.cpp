#include <iostream>
#include <string>
#include <numeric>
#include <memory>
#include "Day11.h"
#include "Monkeys.h"


std::vector<std::string> Day11::run(std::ifstream &input) {
    std::vector<std::string> out;
    auto m = std::make_unique<Monkeys>(input);
    for(int i = 0; i < 20; i++) {m->runRound();}
    out.push_back(std::to_string(m->getMonkeyBusiness()));
    input.clear(); input.seekg(0);
    auto m2 = std::make_unique<Monkeys>(input, 1);
    for(int i = 0; i < 10000; i++) {m2->runRound();}
    out.push_back(std::to_string(m2->getMonkeyBusiness()));
    return out;
}