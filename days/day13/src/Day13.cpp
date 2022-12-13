#include <iostream>
#include <string>
#include <memory>
#include "Day13.h"
#include "Message.h"


std::vector<std::string> Day13::run(std::ifstream &input) {
    std::vector<std::string> out;
    auto ret = getSortScores(input);
    out.push_back(std::to_string(ret.first));
    out.push_back(std::to_string(ret.second));
    return out;
}

std::pair<unsigned int, unsigned int> Day13::getSortScores(std::istream &input) {
    auto m = std::make_unique<Message>();
    bool cont = true;
    while(cont) {
        std::string line1;
        std::string line2;
        std::string line3;
        std::getline(input, line1);
        std::getline(input, line2);
        cont = (bool)std::getline(input, line3);
        m->parsePair(line1, line2);
    }
    return {m->getOrderedPairScore(), m->getTotalSortScore()};
}