#include <gtest/gtest.h>
#include <memory>
#include "Day18.h"
#include "CubeMap.h"
// Demonstrate some basic assertions for new class.
TEST(Day18Test, Part1Part2) {
    std::stringstream in;
    in << "2,2,2\n";
    in << "1,2,2\n";
    in << "3,2,2\n";
    in << "2,1,2\n";
    in << "2,3,2\n";
    in << "2,2,1\n";
    in << "2,2,3\n";
    in << "2,2,4\n";
    in << "2,2,6\n";
    in << "1,2,5\n";
    in << "3,2,5\n";
    in << "2,1,5\n";
    in << "2,3,5\n";
    //in << "1,1,1\n";
    //in << "2,1,1\n";
    auto c = std::make_unique<CubeMap>();
    for(std::string readline; std::getline(in, readline);) {
        c->addPoint(readline);
    }
    ASSERT_EQ(c->getFaces(), 64);
    ASSERT_EQ(c->getExteriorArea(), 58);
}
