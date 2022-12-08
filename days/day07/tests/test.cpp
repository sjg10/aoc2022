#include <gtest/gtest.h>
#include "Day07.h"
#include "Directories.h"
// Demonstrate some basic assertions for new class.
TEST(Day07Test, Part1Part2) {
    std::stringstream in;
    in << "$ cd /\n";
    in << "$ ls\n";
    in << "dir a\n";
    in << "14848514 b.txt\n";
    in << "8504156 c.dat\n";
    in << "dir d\n";
    in << "$ cd a\n";
    in << "$ ls\n";
    in << "dir e\n";
    in << "29116 f\n";
    in << "2557 g\n";
    in << "62596 h.lst\n";
    in << "$ cd e\n";
    in << "$ ls\n";
    in << "584 i\n";
    in << "$ cd ..\n";
    in << "$ cd ..\n";
    in << "$ cd d\n";
    in << "$ ls\n";
    in << "4060174 j\n";
    in << "8033020 d.log\n";
    in << "5626152 d.ext\n";
    in << "7214296 k\n";
    auto root = std::make_unique<DirectoryRoot>();
    for(std::string readline; std::getline(in, readline);) {
        root->parseInput(readline);
    }
    ASSERT_EQ(root->getSmallDirScore(), 95437);
    ASSERT_EQ(root->getDeleteCandidate(), 24933642);
}
