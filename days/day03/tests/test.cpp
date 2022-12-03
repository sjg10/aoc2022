#include <gtest/gtest.h>
#include <memory>
#include "Day03.h"
#include "Rucksacks.h"


// Demonstrate some basic assertions for new class.
/*
TEST(Day03Test, RucksackCreate) {
    std::stringstream in;
    in << "vJrwpWtwJgWrhcsFMMfFFhFp\n";
    in << "jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL\n";
    auto r = std::make_unique<Rucksack>(in);
    ASSERT_EQ(r->getDoubledItem(),16);
    auto r2 = std::make_unique<Rucksack>(in);
    ASSERT_EQ(r2->getDoubledItem(),38);
}
TEST(Day03Test, RucksackSum) {
    std::stringstream in;
    in << "vJrwpWtwJgWrhcsFMMfFFhFp\n";
    in << "jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL\n";
    in << "PmmdzqPrVvPwwTWBwg\n";
    in << "wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn\n";
    in << "ttgJtRGJQctTZtZT\n";
    in << "CrZsJsPPZsGzwwsLwLmpwMDw\n";
    auto d = std::make_unique<Day03>();
    d->compileRucksacks(in);
    ASSERT_EQ(d->getRucksackScore(), 157);
}
*/
TEST(Day03Test, Part1) {
    std::stringstream in;
    in << "vJrwpWtwJgWrhcsFMMfFFhFp\n";
    in << "jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL\n";
    in << "PmmdzqPrVvPwwTWBwg\n";
    in << "wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn\n";
    in << "ttgJtRGJQctTZtZT\n";
    in << "CrZsJsPPZsGzwwsLwLmpwMDw\n";
    auto r = std::make_unique<Rucksacks>(in);
    auto b = r->getIntersects();
    ASSERT_EQ(b[0], 16);
    ASSERT_EQ(b[1], 38);
}

TEST(Day03Test, Part2) {
    std::stringstream in;
    in << "vJrwpWtwJgWrhcsFMMfFFhFp\n";
    in << "jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL\n";
    in << "PmmdzqPrVvPwwTWBwg\n";
    in << "wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn\n";
    in << "ttgJtRGJQctTZtZT\n";
    in << "CrZsJsPPZsGzwwsLwLmpwMDw\n";
    auto r = std::make_unique<Rucksacks>(in);
    auto b = r->getBadges();
    ASSERT_EQ(b[0], 18);
    ASSERT_EQ(b[1], 52);
}