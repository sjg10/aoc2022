#include <gtest/gtest.h>
#include "Day06.h"
// Demonstrate some basic assertions for new class.
TEST(Day06Test, Part1) {
    EXPECT_EQ(Day06::getPreambleStart("bvwbjplbgvbhsrlpgdmjqwftvncz"), 5);
    EXPECT_EQ(Day06::getPreambleStart("nppdvjthqldpwncqszvftbrmjlhg"), 6);
    EXPECT_EQ(Day06::getPreambleStart("nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg"), 10);
    EXPECT_EQ(Day06::getPreambleStart("zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw"), 11);
}
TEST(Day06Test, Part2) {
    EXPECT_EQ(Day06::getPreambleStart("mjqjpqmgbljsphdztnvjfqwrcgsmlb", 14), 19);
    EXPECT_EQ(Day06::getPreambleStart("bvwbjplbgvbhsrlpgdmjqwftvncz", 14), 23);
    EXPECT_EQ(Day06::getPreambleStart("nppdvjthqldpwncqszvftbrmjlhg", 14), 23);
    EXPECT_EQ(Day06::getPreambleStart("nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg", 14), 29);
    EXPECT_EQ(Day06::getPreambleStart("zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw", 14), 26);
}
