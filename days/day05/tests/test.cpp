#include <gtest/gtest.h>
#include "Day05.h"
// Demonstrate some basic assertions for new class.
TEST(Day05Test, Part1Part2) {
    std::stringstream in;
    in << "    [D]    \n";
    in << "[N] [C]    \n";
    in << "[Z] [M] [P]\n";
    in << " 1   2   3 \n";
    in << "\n";
    in << "move 1 from 2 to 1\n";
    in << "move 3 from 1 to 3\n";
    in << "move 2 from 2 to 1\n";
    in << "move 1 from 1 to 2\n";
    auto ret = Day05::getStackTops(in);
    ASSERT_EQ(ret.first, "CMZ");
    ASSERT_EQ(ret.second, "MCD");
}
