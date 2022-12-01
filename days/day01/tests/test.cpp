#include <gtest/gtest.h>
#include "Day01.h"
// Demonstrate some basic assertions for new class.
TEST(Day01Test, Part1Part2) {
    std::stringstream in;
    in << "1000\n";
    in << "2000\n";
    in << "3000\n";
    in << "\n";
    in << "4000\n";
    in << "\n";
    in << "5000\n";
    in << "6000\n";
    in << "\n";
    in << "7000\n";
    in << "8000\n";
    in << "9000\n";
    in << "\n";
    in << "10000\n";
    auto maximum = Day01::getMaxElf(in);
    ASSERT_EQ(maximum[0].first, 3);
    ASSERT_EQ(maximum[0].second, 24000);
    auto maximums = Day01::getMaxElf(in, 3);
    ASSERT_EQ(maximum[0].first, 3);
    ASSERT_EQ(maximum[0].second, 24000);
    ASSERT_EQ(maximum[1].first, 2);
    ASSERT_EQ(maximum[1].second, 11000);
    ASSERT_EQ(maximum[2].first, 4);
    ASSERT_EQ(maximum[2].second, 10000);
}
