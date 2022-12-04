#include <gtest/gtest.h>
#include "Day04.h"
// Demonstrate some basic assertions for new class.
TEST(Day04Test, Part1Part2) {
    std::stringstream in;
    in << "2-4,6-8\n";
    in << "2-3,4-5\n";
    in << "5-7,7-9\n";
    in << "2-8,3-7\n";
    in << "6-6,4-6\n";
    in << "2-6,4-8\n";
    auto r = Day04::getOverlaps(in);
    ASSERT_EQ(r.first, 2);
    ASSERT_EQ(r.second, 4);
}
