#include <gtest/gtest.h>
#include <memory>
#include "Day16.h"
#include "Volcano.h"
// Demonstrate some basic assertions for new class.
TEST(Day16Test, Part1Part2) {
    std::stringstream in;
    in << "Valve AA has flow rate=0; tunnels lead to valves DD, II, BB\n";
    in << "Valve BB has flow rate=13; tunnels lead to valves CC, AA\n";
    in << "Valve CC has flow rate=2; tunnels lead to valves DD, BB\n";
    in << "Valve DD has flow rate=20; tunnels lead to valves CC, AA, EE\n";
    in << "Valve EE has flow rate=3; tunnels lead to valves FF, DD\n";
    in << "Valve FF has flow rate=0; tunnels lead to valves EE, GG\n";
    in << "Valve GG has flow rate=0; tunnels lead to valves FF, HH\n";
    in << "Valve HH has flow rate=22; tunnel leads to valve GG\n";
    in << "Valve II has flow rate=0; tunnels lead to valves AA, JJ\n";
    in << "Valve JJ has flow rate=21; tunnel leads to valve II\n";
    auto v = std::make_unique<Volcano>();
    for (std::string read_line; std::getline(in, read_line);) {
        v->addRoom(read_line);
    }
    ASSERT_EQ(v->getBestPressure(), 1651);
    ASSERT_EQ(v->getBestElephantPressure(), 1707);
    
}
