#include <gtest/gtest.h>
#include "Day12.h"
#include "Map.h"
// Demonstrate some basic assertions for new class.
TEST(Day12Test, Part1Part2) {
    std::stringstream in;
    in << "Sabqponm\n";
    in << "abcryxxl\n";
    in << "accszExk\n";
    in << "acctuvwj\n";
    in << "abdefghi\n";
    auto m = std::make_unique<Map>(in);
    ASSERT_EQ(m->getShortestPathForward(), 31);
    ASSERT_EQ(m->getShortestPathBackward(), 29);
}
