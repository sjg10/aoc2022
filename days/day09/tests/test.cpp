#include <gtest/gtest.h>
#include "Day09.h"
#include "Rope.h"
// Demonstrate some basic assertions for new class.
TEST(Day09Test, Part1Part2) {
    std::stringstream in;
    in << "R 4\n";
    in << "U 4\n";
    in << "L 3\n";
    in << "D 1\n";
    in << "R 4\n";
    in << "D 1\n";
    in << "L 5\n";
    in << "R 2\n";
    auto r = std::make_unique<Rope>(2);
    auto r2 = std::make_unique<Rope>(10);
    for(std::string readline; std::getline(in,readline);) {
        r->moveHead(readline);
        r2->moveHead(readline);
    }
    ASSERT_EQ(r->getTailPositions(),13);
    ASSERT_EQ(r2->getTailPositions(),1);
}

TEST(Day09Test, Part2) {
    std::stringstream in;
    in << "R 5\n";
    in << "U 8\n";
    in << "L 8\n";
    in << "D 3\n";
    in << "R 17\n";
    in << "D 10\n";
    in << "L 25\n";
    in << "U 20\n";
    auto r = std::make_unique<Rope>(10);
    for(std::string readline; std::getline(in,readline);) {
        r->moveHead(readline);
    }
    ASSERT_EQ(r->getTailPositions(),36);
}