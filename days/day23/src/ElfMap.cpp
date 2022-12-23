#include "ElfMap.h"
#include <map>
#include <iostream>
bool Elf::proposeMove(std::vector<std::vector<bool>> &elf_locator) {
    instruction_offset++;
    instruction_offset %=4;
    newx = x; newy = y;
    //std::cout << x << "," << y <<std::endl; 
    bool N = elf_locator[x - 1][y];
    bool S = elf_locator[x + 1][y];
    bool E = elf_locator[x][y + 1];
    bool W = elf_locator[x][y - 1];
    bool NE = elf_locator[x - 1][y + 1];
    bool NW = elf_locator[x - 1][y - 1];
    bool SE = elf_locator[x + 1][y + 1];
    bool SW = elf_locator[x + 1][y - 1];
    if (!(N || S || E || W || NW ||NE ||SE ||SW)) { return false; }
    else {
        unsigned int i  = instruction_offset;
        do {
            if(i == 0 && !(N || NE || NW)) {newx--; /*std::cout << "N" << std::endl;*/ return true;}
            if(i == 1 && !(S || SE || SW)) {newx++; /*std::cout << "S" << std::endl;*/ return true;}
            if(i == 2 && !(W || NW || SW)) {newy--; /*std::cout << "W" << std::endl;*/ return true;}
            if(i == 3 && !(E || NE || SE)) {newy++; /*std::cout << "E" << std::endl;*/ return true;}
            i++;
            i %= 4;
        } while (i != instruction_offset);
    }
    return false;
}

void Elf::move() {
   //std::cout <<"mo " << x << "," << y <<std::endl; 

    x = newx;
    y = newy;
}

std::pair<int,int> Elf::getNextPosition() {
    return {newx, newy};
}


std::pair<int,int> Elf::getPosition() {
    return {x, y};
}


bool ElfMap::moveElves() {
    std::map<std::pair<int,int>, std::vector<unsigned int>> moves;
    std::vector<std::vector<bool>> elf_locator = std::vector(xshift * 2, std::vector(yshift * 2, false));
    for (unsigned int i = 0; i < elves.size(); i++) {
        auto p = elves[i]->getPosition();
        elf_locator[p.first][p.second] = true;
    }
    bool fin = true;
/*

    // Test prnt
    int xmin = 2 * xshift;
    int xmax = 0;
    int ymin = 2 * yshift;
    int ymax = 0;
    for (unsigned int i = 0; i < elves.size(); i++) {
        auto p = elves[i]->getPosition();
        if(p.first > xmax) { xmax = p.first;}
        if(p.first < xmin) { xmin = p.first;}
        if(p.second > ymax) { ymax = p.second;}
        if(p.second < ymin) { ymin = p.second;}
    }
    for (int x = xmin; x <= xmax; x++) {
        for (int y = ymin; y <= ymax; y++) {
            if (elf_locator[x][y]) { std::cout << "#";}
            else { std::cout << ".";}
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
*/



    for (unsigned int i = 0; i < elves.size(); i++) {
        if (elves[i]->proposeMove(elf_locator)) {
            auto pos = elves[i]->getNextPosition();
            if (moves.find(pos) == moves.end()) {
                moves[pos] = {i};
            } else {moves[pos].push_back(i);}
        }
    }
    for (auto const &m: moves) {
        if (m.second.size() == 1) {
            fin = false;
            elves[m.second[0]]->move();
        }
    }
    return fin;

}

ElfMap::ElfMap(std::istream &in) {
    int x = xshift;
    int y = yshift;
    for(std::string readline; std::getline(in, readline);) {
        for (unsigned int i = 0; i < readline.size(); i++) {
            if (readline[i] == '#') {
                elves.push_back(std::make_unique<Elf>(x,y));
            }
            y++;
        }
        x++;
        y = yshift;
    }
}

unsigned int ElfMap::getElfScore() {
    int xmin = 2 * xshift;
    int xmax = 0;
    int ymin = 2 * yshift;
    int ymax = 0;
    for (unsigned int i = 0; i < elves.size(); i++) {
        auto p = elves[i]->getPosition();
        if(p.first > xmax) { xmax = p.first;}
        if(p.first < xmin) { xmin = p.first;}
        if(p.second > ymax) { ymax = p.second;}
        if(p.second < ymin) { ymin = p.second;}
    }
    return (((ymax - ymin) + 1) * ((xmax - xmin) + 1)) - elves.size();
}
