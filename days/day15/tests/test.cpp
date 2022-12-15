#include <gtest/gtest.h>
#include "Day15.h"
#include "BeaconMap.h"
// Demonstrate some basic assertions for new class.
TEST(Day15Test, Part1Part2) {
    std::stringstream in;
    in << "Sensor at x=2, y=18: closest beacon is at x=-2, y=15\n";
    in << "Sensor at x=9, y=16: closest beacon is at x=10, y=16\n";
    in << "Sensor at x=13, y=2: closest beacon is at x=15, y=3\n";
    in << "Sensor at x=12, y=14: closest beacon is at x=10, y=16\n";
    in << "Sensor at x=10, y=20: closest beacon is at x=10, y=16\n";
    in << "Sensor at x=14, y=17: closest beacon is at x=10, y=16\n";
    in << "Sensor at x=8, y=7: closest beacon is at x=2, y=10\n";
    in << "Sensor at x=2, y=0: closest beacon is at x=2, y=10\n";
    in << "Sensor at x=0, y=11: closest beacon is at x=2, y=10\n";
    in << "Sensor at x=20, y=14: closest beacon is at x=25, y=17\n";
    in << "Sensor at x=17, y=20: closest beacon is at x=21, y=22\n";
    in << "Sensor at x=16, y=7: closest beacon is at x=15, y=3\n";
    in << "Sensor at x=14, y=3: closest beacon is at x=15, y=3\n";
    in << "Sensor at x=20, y=1: closest beacon is at x=15, y=3\n";
    auto b = std::make_unique<BeaconMap>(in);
    ASSERT_EQ(b->getRowPositions(10), 26);
    ASSERT_EQ(b->findBeacon(20), 56000011);
}
