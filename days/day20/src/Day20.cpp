#include <iostream>
#include <string>
#include <memory>
#include "Day20.h"
#include "Messager.h"


std::vector<std::string> Day20::run(std::ifstream &input) {
    std::vector<std::string> out;    
    auto m = std::make_unique<Messager>(input);
    m->mix();
    out.push_back(std::to_string(m->getScore()));
    input.clear(); input.seekg(0);

    auto m2 = std::make_unique<Messager>(input, 811589153);
    for(unsigned int i = 0; i < 10; i++) {m2->mix();}
    out.push_back(std::to_string(m2->getScore()));
    return out;
}