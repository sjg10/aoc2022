#include <gtest/gtest.h>
#include <memory>
#include "Day21.h"
#include "MonkeyMaths.h"
// Demonstrate some basic assertions for new class.
TEST(Day21Test, Part1Part2) {
    std::stringstream in;
    in << "root: pppw + sjmn\n";
    in << "dbpl: 5\n";
    in << "cczh: sllz + lgvd\n";
    in << "zczc: 2\n";
    in << "ptdq: humn - dvpt\n";
    in << "dvpt: 3\n";
    in << "lfqf: 4\n";
    in << "humn: 5\n";
    in << "ljgn: 2\n";
    in << "sjmn: drzm * dbpl\n";
    in << "sllz: 4\n";
    in << "pppw: cczh / lfqf\n";
    in << "lgvd: ljgn * ptdq\n";
    in << "drzm: hmdt - zczc\n";
    in << "hmdt: 32\n";
    auto m = std::make_unique<MonkeyMaths>(in);
    ASSERT_EQ(m->getRootScore(), 152);
    ASSERT_EQ(m->getHumanScore(), 301); // wont pass: herusistic solution
    
}