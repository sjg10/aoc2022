#include <gtest/gtest.h>
#include "Day13.h"

// Demonstrate some basic assertions for new class.
TEST(Day13Test, Part1Part2) {
    std::stringstream in;
    in << "[1,1,3,1,1]\n";
    in << "[1,1,5,1,1]\n";
    in << "\n";
    in << "[[1],[2,3,4]]\n";
    in << "[[1],4]\n";
    in << "\n";
    in << "[9]\n";
    in << "[[8,7,6]]\n";
    in << "\n";
    in << "[[4,4],4,4]\n";
    in << "[[4,4],4,4,4]\n";
    in << "\n";
    in << "[7,7,7,7]\n";
    in << "[7,7,7]\n";
    in << "\n";
    in << "[]\n";
    in << "[3]\n";
    in << "\n";
    in << "[[[]]]\n";
    in << "[[]]\n";
    in << "\n";
    in << "[1,[2,[3,[4,[5,6,7]]]],8,9]\n";
    in << "[1,[2,[3,[4,[5,6,0]]]],8,9]\n";
    auto ret = Day13::getSortScores(in);
    ASSERT_EQ(ret.first,  13);
    ASSERT_EQ(ret.second,  140);
}
