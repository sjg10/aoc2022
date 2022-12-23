#include <gtest/gtest.h>
#include <memory>
#include "ElfMap.h"
#include "Day23.h"
// Demonstrate some basic assertions for new class.
TEST(Day23Test, Part1Part2) {
    std::stringstream in;
    in << "....#..\n";
    in << "..###.#\n";
    in << "#...#.#\n";
    in << ".#...##\n";
    in << "#.###..\n";
    in << "##.#.##\n";
    in << ".#..#..\n";
    /*in << ".....\n";
    in << "..##.\n";
    in << "..#..\n";
    in << ".....\n";
    in << "..##.\n";
    in << ".....\n";*/
    auto m = std::make_unique<ElfMap>(in); 
    for(unsigned int i=0 ; i < 10; i++) {
        ASSERT_FALSE(m->moveElves());
    }
    ASSERT_EQ(m->getElfScore(),110);
    for(unsigned int i=0 ; i < 9; i++) {
        ASSERT_FALSE(m->moveElves());
    }
    ASSERT_TRUE(m->moveElves());

}
