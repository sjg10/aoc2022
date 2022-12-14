#include <gtest/gtest.h>
#include <memory>
#include "Day14.h"
#include "Cave.h"
// Demonstrate some basic assertions for new class.
TEST(Day14Test, Part1Part2) {
    std::stringstream in;
    in << "498,4 -> 498,6 -> 496,6\n";
    in << "503,4 -> 502,4 -> 502,9 -> 494,9\n";
    auto c = std::make_unique<Cave>();

    for (std::string read_line; std::getline(in, read_line);) {
        c->addLine(read_line);
    }
    bool cont = true;
    do {
        cont = c->addSand();
    } while(cont);
    ASSERT_EQ(c->getSandCount(), 24);
    ASSERT_EQ(c->getSandCountFloored(), 93);
}
