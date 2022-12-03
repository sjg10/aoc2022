#include "Rucksacks.h"
#include <algorithm>
#include <cassert>

Rucksacks::Rucksacks(std::istream &input) {
    char c;
    rucksacks.push_back({});
    while (input.get(c)) {
        if (c == '\n') {
            rucksack_pockets.push_back(std::make_pair(
                std::vector<unsigned int>(rucksacks.back().begin(), rucksacks.back().begin() + rucksacks.back().size() / 2),
                std::vector<unsigned int>(rucksacks.back().begin() + rucksacks.back().size() / 2, rucksacks.back().end())
                )
            );
            std::sort(rucksack_pockets.back().first.begin(), rucksack_pockets.back().first.end());
            std::sort(rucksack_pockets.back().second.begin(), rucksack_pockets.back().second.end());
            std::sort(rucksacks.back().begin(), rucksacks.back().end()); // TODO: part 1 again!
            rucksacks.push_back({});
        }
        else {
            unsigned int val = ((c >='a') ? ((c-'a') + 1) : ((c-'A') + 27));
            rucksacks.back().push_back(val);
        }
    }
    rucksacks.pop_back();
}


std::vector<unsigned int> Rucksacks::getIntersects() {
    std::vector<unsigned int> ret;
    for(auto const &itr: rucksack_pockets) {
        std::vector<unsigned int> intermediate;
        std::set_intersection(
            itr.first.begin(), itr.first.end(),
            itr.second.begin(), itr.second.end(),
            std::back_inserter(intermediate)
        );
        assert(intermediate.size() >= 1); /* expected input should guarantee one intersect*/
        ret.push_back(intermediate[0]);
    }
    return ret;
}

std::vector<unsigned int> Rucksacks::getBadges() {
    std::vector<unsigned int> ret;
    for (unsigned int i = 0; i < rucksacks.size(); i+=3) {
        std::vector<unsigned int> intermediate1;
        std::vector<unsigned int> intermediate2;
        std::set_intersection(
            rucksacks[i].begin(), rucksacks[i].end(),
            rucksacks[i+1].begin(), rucksacks[i+2].end(),
            std::back_inserter(intermediate1)
        );
        std::set_intersection(
            rucksacks[i+2].begin(), rucksacks[i+2].end(),
            intermediate1.begin(), intermediate1.end(),
            std::back_inserter(intermediate2)
        );
        assert(intermediate2.size() >= 1);
        ret.push_back(intermediate2[0]);
    }
    return ret;
}
