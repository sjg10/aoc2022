#include <gtest/gtest.h>
#include "Day08.h"
// Demonstrate some basic assertions for new class.
TEST(Day08Test, Part1Part2) {
    std::stringstream in;
    in << "30373\n";
    in << "25512\n";
    in << "65332\n";
    in << "33549\n";
    in << "35390\n";
    auto forest = Day08::parseInput(in);
    auto ret = Day08::visibleCount(forest);
    ASSERT_EQ(ret.first, 21);
    ASSERT_EQ(ret.second, 8);
}
