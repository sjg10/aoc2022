#include "CPU.h"
#include <cassert>
#include <iostream>
#include <sstream>

void CPU::parseCommand(std::string input) {
    auto spacesep = input.find(" ");
    std::string instruction = input.substr(0, spacesep);
    if (instruction == "addx") {
        int v = std::stol(input.substr(spacesep + 1));
        addx(v);
    }
    else if (instruction == "noop") {
        noop();
    }
    else {
        assert(false); //unknown op
    }
}

void CPU::noop() {
    cycleToValue.push_back(X);
    cycle++;
}

void CPU::addx(int v) {
    cycleToValue.push_back(X);
    cycleToValue.push_back(X);
    cycle++;
    X += v;
    cycle++;
}

int CPU::getSignalStrengthTotal() {
    int sum = 0;
    for(int i = 20; i <= 220; i+=40) {
        sum += i * cycleToValue[i];
    }
    return sum;
}

std::string CPU::drawScreen() {
    std::stringstream ss;
    for(int i = 0; i < 240; i++) {
        int horizantal = (i % 40);
        int X = cycleToValue[i + 1];
        if (horizantal >= X - 1 && horizantal <= X + 1) {
            ss << "#";
        }
        else {
            ss << ".";
        }
        if (horizantal == 39) {
            ss << "\n";
        }
    }
    return ss.str();
}