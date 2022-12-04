#include <iostream>
#include <string>
#include <numeric>
#include "Day04.h"


std::vector<std::string> Day04::run(std::ifstream &input) {
    std::vector<std::string> out;
    auto ret = getOverlaps(input);
    out.push_back(std::to_string(ret.first));
    out.push_back(std::to_string(ret.second));
    return out;
}

std::pair<unsigned int,unsigned int> Day04::getOverlaps(std::istream &input) {
    unsigned int ret1 = 0;
    unsigned int ret2 = 0;
    for(std::string read_line; std::getline(input, read_line);) {
        unsigned int dash1 = read_line.find("-");
        unsigned int comma = read_line.find(",");
        unsigned int dash2 = read_line.find("-",dash1 + 1);
        unsigned int a_l = std::stoul(read_line.substr(0, dash1));
        unsigned int a_u = std::stoul(read_line.substr(dash1 + 1, comma - dash1));
        unsigned int b_l = std::stoul(read_line.substr(comma + 1, dash2 - comma));
        unsigned int b_u = std::stoul(read_line.substr(dash2 + 1));
        ret1 += ((a_l >= b_l && a_u <= b_u )|| (b_l >= a_l && b_u <= a_u));
        ret2 += ((a_l <= b_u && a_u >= b_l) || (b_l <= a_u && b_u >= a_l));
    }
    return {ret1,ret2};
}
