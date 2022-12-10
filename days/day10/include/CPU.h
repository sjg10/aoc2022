#pragma once
#include <string>
#include <vector>

class CPU {
public:
    CPU() {}
    void parseCommand(std::string input);
    int getSignalStrengthTotal();
    std::string drawScreen();
private:
    void addx(int v);
    void noop();
    int cycle = 1;
    int X = 1;
    std::vector<int> cycleToValue = {1};
};