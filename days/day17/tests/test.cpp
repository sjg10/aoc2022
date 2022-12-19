#include <gtest/gtest.h>
#include <memory>
#include "Day17.h"
#include "RockSim.h"
// Demonstrate some basic assertions for new class.
TEST(Day17Test, Part1Part2) {
    std::stringstream in;
    in << ">>><<><>><<<>><>>><<<>>><<<><<<>><>><<>>\n";
    std::string jetline;
    std::getline(in, jetline);
    auto s = std::make_unique<RockSim>(jetline);
    s->run(2022);
    ASSERT_EQ(s->getTowerHeight(),3068);
    //s->run(1000000000000 - 2022);
    //ASSERT_EQ(s->getTowerHeight(),1514285714288);
}
