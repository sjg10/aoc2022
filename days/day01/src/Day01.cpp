#include <iostream>
#include <string>
#include <numeric>
#include "Day01.h"


std::vector<std::string> Day01::run(std::ifstream &input) {
    std::vector<std::string> out;
    auto res = getMaxElf(input, 3);
    out.push_back(std::to_string(res.front().second));
    auto total = std::accumulate(res.begin(), res.end(), 0, [&](int a, std::pair<unsigned int,unsigned int> b){return a + b.second;});
    out.push_back(std::to_string(total));
    return out;
}


std::list<std::pair<unsigned int,unsigned int>> Day01::getMaxElf(std::istream &input, unsigned int elves) {
    std::list<std::pair<unsigned int,unsigned int>> maximums{elves, {0,0}};
    unsigned int running_total = 0;
    unsigned int current_elf = 0;
    for(std::string read_string; std::getline(input, read_string);) {
        if (!read_string.empty()) { // if there is data, add it to the total
            running_total += std::stoul(read_string);
        }
        if(read_string.empty() || input.peek() == EOF) { // if this is an empty line or the last line, examine this finished elf
            for( auto itr = maximums.begin(); itr != maximums.end(); itr++ ) {
                if(running_total > itr->second) {
                    maximums.insert(itr, std::make_pair(current_elf,running_total));
                    maximums.pop_back();
                    break;
                }
            }
            current_elf++;
            running_total = 0;
        }
    }
    return maximums;
}