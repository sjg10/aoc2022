#include <gtest/gtest.h>
#include <memory>
#include "Day19.h"
#include "GeodeFactory.h"
// Demonstrate some basic assertions for new class.
TEST(Day19Test, Part1Part2) {
    std::stringstream in;
    in  << "Blueprint 1: ";
    in  << "Each ore robot costs 4 ore. ";
    in  << "Each clay robot costs 2 ore. ";
    in  << "Each obsidian robot costs 3 ore and 14 clay. ";
    in  << "Each geode robot costs 2 ore and 7 obsidian.";
    in  << "\n";
    in  << "Blueprint 2: ";
    in  << "Each ore robot costs 2 ore. ";
    in  << "Each clay robot costs 3 ore. ";
    in  << "Each obsidian robot costs 3 ore and 8 clay. ";
    in  << "Each geode robot costs 3 ore and 12 obsidian.";
    in  << "\n";
    auto gf = std::make_unique<Factory>();
    for(std::string readline; std::getline(in, readline);) {
        gf->loadBlueprint(readline);
    }
    ASSERT_EQ(gf->getTotalScore(),33);
}
