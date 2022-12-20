#include <gtest/gtest.h>
#include <memory>
#include "Day20.h"
#include "Messager.h"
// Demonstrate some basic assertions for new class.
TEST(Day20Test, Part1) {
    std::stringstream in;
    in << "1\n";
    in << "2\n";
    in << "-3\n";
    in << "3\n";
    in << "-2\n";
    in << "0\n";
    in << "4\n";
    auto m = std::make_unique<Messager>(in);
    m->mix();
    ASSERT_EQ(m->getScore(), 3);
}

TEST(Day20Test, Part2) {
    std::stringstream in;
    in << "1\n";
    in << "2\n";
    in << "-3\n";
    in << "3\n";
    in << "-2\n";
    in << "0\n";
    in << "4\n";
    auto m = std::make_unique<Messager>(in,811589153);
    for(unsigned int i = 0; i < 10; i++) {m->mix();}
    ASSERT_EQ(m->getScore(), 1623178306);
}
