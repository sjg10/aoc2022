#include <gtest/gtest.h>
#include "Day02.h"
// Demonstrate some basic assertions for new class.
TEST(Day02Test, Part1Part2) {
    std::stringstream in;
    in << "A Y\n";
    in << "B X\n";
    in << "C Z\n";
    auto score = Day02::scoreRPS(in);
    ASSERT_EQ(score.first, 15);
    ASSERT_EQ(score.second, 12);
}