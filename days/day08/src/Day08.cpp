#include <iostream>
#include <string>
#include <numeric>
#include "Day08.h"


std::vector<std::string> Day08::run(std::ifstream &input) {
    std::vector<std::string> out;
    auto forest = parseInput(input);
    auto ret = visibleCount(forest);
    out.push_back(std::to_string(ret.first));
    out.push_back(std::to_string(ret.second));
    return out;
}

std::vector<std::vector<Tree>>  Day08::parseInput(std::istream &input) {
    std::vector<std::vector<Tree>> forest;
    for (std::string readline; std::getline(input, readline);) {
        forest.push_back({});
        for (auto const &c : readline) {
            forest.back().push_back(
                {(unsigned int)c - '0', 0, 0, 0, 0, false}
            );
        }
    }
    return forest;
}

std::pair<unsigned int,unsigned int> Day08::visibleCount(std::vector<std::vector<Tree>> &forest) {
    unsigned int n = forest.size();
    unsigned int visible = 0;
    unsigned int max;
    // check rows
    for (unsigned int row = 1; row < n - 1; row++) {
        // check left to right
        max = forest[row][0].val;
        for (unsigned int col = 1; col < n - 1; col++) { 
            if (forest[row][col].val > max) {
                max = forest[row][col].val;
                if (!forest[row][col].detected_visible) {
                    forest[row][col].detected_visible = true;
                    visible++;
                }
            }
            for(unsigned int i = 1; i <= col ; i++) { // check scenic
                forest[row][col].scenic_left++;
                if (forest[row][col].val <= forest[row][col - i].val) {
                    break;
                }
            }
        }
        // check right to left
        max = forest[row][n - 1].val;
        for (unsigned int col = n - 2; col > 0; col--) { 
            if (forest[row][col].val >  max) {
                max = forest[row][col].val;
                if (!forest[row][col].detected_visible) {
                    forest[row][col].detected_visible = true;
                    visible++;
                }
            }
            for(unsigned int i = 1; i <= (n - 1) - (col) ; i++) { // check scenic
                forest[row][col].scenic_right++;
                if (forest[row][col].val <= forest[row][col + i].val) {
                    break;
                }
            }
        }
    }
    //check columns
    for (unsigned int col = 1; col < n - 1; col++) {
        // check top to bottom
        max = forest[0][col].val;
        for (unsigned int row = 1; row < n - 1; row++) { 
            if (forest[row][col].val >  max) {
                max = forest[row][col].val;
                if (!forest[row][col].detected_visible) {
                    forest[row][col].detected_visible = true;
                    visible++;
                }
            }
            for(unsigned int i = 1; i <= row ; i++) { // check scenic
                forest[row][col].scenic_up++;
                if (forest[row][col].val <= forest[row - i][col].val) {
                    break;
                }
            }
        }
        // check bottom to top
        max = forest[n - 1][col].val;
        for (unsigned int row = n - 2; row > 0; row--) { 
            if (forest[row][col].val >  max) {
                max = forest[row][col].val;
                if (!forest[row][col].detected_visible) {
                    forest[row][col].detected_visible = true;
                    visible++;
                }
            }
            for(unsigned int i = 1; i <= (n - 1) - (row) ; i++) { // check scenic
                forest[row][col].scenic_down++;
                if (forest[row][col].val <= forest[row + i][col].val) {
                    break;
                }
            }
        }
    }

    // one last loop to find highest scenic score (ignore outside, they are all zero)
    unsigned int max_score = 0;
    for (unsigned int row = 1; row < n - 1; row++) {
        for (unsigned int col = 1; col < n - 1; col++) {
            unsigned int score = 
                forest[row][col].scenic_down * 
                forest[row][col].scenic_up   * 
                forest[row][col].scenic_left * 
                forest[row][col].scenic_right;
            if (score > max_score) {
                max_score = score;
            }
        }
    }

    // add on the edges for visible count - all visible
    return {visible + (4*n - 4), max_score}; 
}