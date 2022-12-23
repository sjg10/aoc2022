#include <iostream>
#include <string>
#include <memory>
#include "Day23.h"
#include "ElfMap.h"


std::vector<std::string> Day23::run(std::ifstream &input) {
    std::vector<std::string> out;
    auto m = std::make_unique<ElfMap>(input); 
    unsigned int i=0;
    for(i=0 ; i < 10; i++) {
        m->moveElves();
    }
    out.push_back(std::to_string(m->getElfScore()));
    while (!m->moveElves())
    {
        i++;
    }
    out.push_back(std::to_string(i+1));
    return out;
}