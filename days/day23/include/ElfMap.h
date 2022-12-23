#pragma once
#include <vector>
#include <memory>

class Elf {
public:
    Elf(int x, int y) : x(x), y(y) {};
    bool proposeMove(std::vector<std::vector<bool>> &elf_locator);
    void move();
    std::pair<int,int> getNextPosition();
    std::pair<int,int> getPosition();
private:
    int x;
    int y;
    int newx;
    int newy;
    unsigned int instruction_offset = 3;
};

class ElfMap {
public:
    ElfMap(std::istream &in);
    bool moveElves();
    unsigned int getElfScore();
private:
    std::vector<std::unique_ptr<Elf>> elves;
    int xshift = 500;
    int yshift = 500;
};