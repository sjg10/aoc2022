#include <gtest/gtest.h>
#include <memory>
#include "Day11.h"
#include "Monkeys.h"
// Demonstrate some basic assertions for new class.
TEST(Day11Test, Part1Part2) {
    std::stringstream in;
    in << "Monkey 0:\n";
    in << "  Starting items: 79, 98\n";
    in << "  Operation: new = old * 19\n";
    in << "  Test: divisible by 23\n";
    in << "    If true: throw to monkey 2\n";
    in << "    If false: throw to monkey 3\n";
    in << "\n";
    in << "Monkey 1:\n";
    in << "  Starting items: 54, 65, 75, 74\n";
    in << "  Operation: new = old + 6\n";
    in << "  Test: divisible by 19\n";
    in << "    If true: throw to monkey 2\n";
    in << "    If false: throw to monkey 0\n";
    in << "\n";
    in << "Monkey 2:\n";
    in << "  Starting items: 79, 60, 97\n";
    in << "  Operation: new = old * old\n";
    in << "  Test: divisible by 13\n";
    in << "    If true: throw to monkey 1\n";
    in << "    If false: throw to monkey 3\n";
    in << "\n";
    in << "Monkey 3:\n";
    in << "  Starting items: 74\n";
    in << "  Operation: new = old + 3\n";
    in << "  Test: divisible by 17\n";
    in << "    If true: throw to monkey 0\n";
    in << "    If false: throw to monkey 1\n";
    auto m = std::make_unique<Monkeys>(in);
    for(int i = 0; i < 20; i++) {m->runRound();}
    ASSERT_EQ(m->getMonkeyBusiness(), 10605);
    in.clear(); in.seekg(0);
    auto m2 = std::make_unique<Monkeys>(in, 1);
    for(int i = 0; i < 10000; i++) {
        std::cout << "== After round "<< i+1 <<"==\n\n";
        m2->runRound();}
    ASSERT_EQ(m2->getMonkeyBusiness(), 2713310158);
}
