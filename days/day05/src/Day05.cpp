#include <iostream>
#include <string>
#include <numeric>
#include <regex>
#include <cassert>
#include "Day05.h"


std::vector<std::string> Day05::run(std::ifstream &input) {
    std::vector<std::string> out;
    auto ret = getStackTops(input);
    out.push_back(ret.first);
    out.push_back(ret.second);
    return out;
}

std::pair<std::string,std::string> Day05::getStackTops(std::istream &input) {
    std::string read_line; std::getline(input, read_line);
    unsigned int stack_count = (read_line.size() + 1) / 4;
    std::vector<std::list<char>> stacks1(stack_count, std::list<char>());

    // Read stacks
    do{
        for(unsigned int i = 0; i < stack_count; i++) {
            char in = read_line.at((i * 4) + 1);
            if (in != ' ') {
                stacks1[i].push_back(read_line.at((i * 4) + 1));
            }
        }
        std::getline(input, read_line);
    } while (read_line.at(0) == '[');

    std::vector<std::list<char>> stacks2(stacks1);

    std::getline(input, read_line); // parse empty line

    //Read instructions
    const std::regex re("move (\\d*) from (\\d*) to (\\d*)");
    for(; std::getline(input, read_line);) {
        std::smatch m;
        std::regex_match(read_line, m, re);
        assert(m.size() == 4);
        unsigned int cnt = std::stoul(m[1]);
        unsigned int from = std::stoul(m[2])- 1;
        unsigned int to = std::stoul(m[3]) - 1;
        // part 1
        for(unsigned int i =0;i < cnt; i++) {
            stacks1[to].push_front(stacks1[from].front());
            stacks1[from].pop_front();
        }
        //part 2
        auto last = stacks2[from].begin();
        std::advance(last, cnt);
        stacks2[to].splice(stacks2[to].begin(),stacks2[from],stacks2[from].begin(), last);
    }
    std::string ret1, ret2;
    for(unsigned int i =0;i < stack_count; i++) {
        ret1 += stacks1[i].front();
        ret2 += stacks2[i].front();
    }
    return {ret1, ret2};
}