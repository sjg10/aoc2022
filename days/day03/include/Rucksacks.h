#pragma once
#include <set>
#include <vector>
#include <istream>

class Rucksacks {
    public:
        /** Create rucksacks */
        Rucksacks(std::istream &input);
        /** returns the items appearing in both pockets of each elf */
        std::vector<unsigned int> getIntersects();
        /** returns the badges for each group of elves */
        std::vector<unsigned int> getBadges();
    private:
        std::vector<std::vector<unsigned int>> rucksacks;
        std::vector<std::pair<std::vector<unsigned int>, std::vector<unsigned int>>> rucksack_pockets;
        std::vector<std::vector<unsigned int>> intersects;
};