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
    ASSERT_EQ(maximum.front().first, 3);
    ASSERT_EQ(maximum.front().second, 24000);
    in.clear(); in.seekg(0);
    auto maximums = Day01::getMaxElf(in, 3);
    ASSERT_EQ(maximums.size(), 3);
    std::vector<std::pair<unsigned int, unsigned int>> exp_maxs = {{3, 24000}, {2, 11000}, {4,10000}};
    unsigned int idx = 0;
    for( auto itr = maximums.begin(); itr != maximums.end(); itr++, idx++) {
        SCOPED_TRACE(idx);
        ASSERT_EQ(*itr,exp_maxs[idx]);
    }
}
