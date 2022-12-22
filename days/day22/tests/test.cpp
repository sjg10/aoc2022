#include <gtest/gtest.h>
#include <memory>
#include "Day22.h"
#include "MonkeyMap.h"
// Demonstrate some basic assertions for new class.
TEST(Day22Test, Part1Part2) {
    std::stringstream in;
    in << "        ...#\n";
    in << "        .#..\n";
    in << "        #...\n";
    in << "        ....\n";
    in << "...#.......#\n";
    in << "........#...\n";
    in << "..#....#....\n";
    in << "..........#.\n";
    in << "        ...#....\n";
    in << "        .....#..\n";
    in << "        .#......\n";
    in << "        ......#.\n";
    in << "\n";
    in << "10R5L5R10L4R5L5\n";
    auto m = std::make_unique<MonkeyMap>(in);
    ASSERT_EQ(m->getScore(),6032);
    ASSERT_EQ(m->getScore(4),5031);
}

/**
10 0 8
5 0 10
5 5 10
10 10 14
4 10 10 
5 5 1
5 5 6


*/