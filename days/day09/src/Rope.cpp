#include "Rope.h"
#include <cassert>

void Rope::moveHead(std::string input) {
    char direction = input[0];
    unsigned int distance = std::stoul(input.substr(2));
    int * val = nullptr;
    int mult = 0;
    switch (direction) {
        case 'R':
            val = &knots.front().first;
            mult = 1;
            break;
        case 'L':
            val = &knots.front().first;
            mult = -1;
            break;
        case 'U':
            val = &knots.front().second;
            mult = 1;
            break;
        case 'D':
            val = &knots.front().second;
            mult = -1;
            break;
        default:
            assert(false);
            break;
    }
    for(unsigned int i = 0; i < distance; i++) {
        *val += mult;
        moveTails();
    }
}


void Rope::moveTails() {
    for (unsigned int i = 1; i < knots.size(); i++) {
        if(
            knots[i].second < knots[i-1].second - 1 ||
            knots[i].second > knots[i-1].second + 1 ||
            knots[i].first < knots[i-1].first - 1 ||
            knots[i].first > knots[i-1].first + 1
        ) {
            if(knots[i].second > knots[i-1].second) {knots[i].second--;}
            else if(knots[i].second < knots[i-1].second) {knots[i].second++;}
            if(knots[i].first > knots[i-1].first) {knots[i].first--;}
            else if(knots[i].first < knots[i-1].first) {knots[i].first++;}
        }        
    }
    tailPositions.insert(knots.back());
}

