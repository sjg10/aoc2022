#include <iostream>
#include <string>
#include <numeric>
#include "Day07.h"
#include "Directories.h"


std::vector<std::string> Day07::run(std::ifstream &input) {
    std::vector<std::string> out;    
    auto root = std::make_unique<DirectoryRoot>();
    for(std::string readline; std::getline(input, readline);) {
        root->parseInput(readline);
    }
    out.push_back(std::to_string(root->getSmallDirScore()));
    out.push_back(std::to_string(root->getDeleteCandidate()));
    return out;
}