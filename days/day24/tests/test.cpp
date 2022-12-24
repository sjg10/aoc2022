#include <gtest/gtest.h>
#include <memory>
#include "Day24.h"
#include "Blizzard.h"
// Demonstrate some basic assertions for new class.
TEST(Day24Test, Part1Part2) {
    std::stringstream in;
    in << "#.######\n";
    in << "#>>.<^<#\n";
    in << "#.<..<<#\n";
    in << "#>v.><>#\n";
    in << "#<^v^^>#\n";
    in << "######.#\n";
    auto b = std::make_unique<BlizzardMap>(in);
    auto res = b->getPathLengths();
    ASSERT_EQ(res.first,18);
    ASSERT_EQ(res.second,54);
}
