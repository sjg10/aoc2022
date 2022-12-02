## Advent Of Code 2022

A CMake/C++17 based project to save Christmas 2022.

Prerequisites are `cmake` and `g++` with versions as specified in `CMakeLists.txt`

To build:

    mkdir build
    cd build
    cmake ..
    make

To run the tests run (from `build`):

    ctest

To run, add the resource files to `res/` and then run (from `build`)

    ./aoc2022

## Tools

Inside `tools/createday` run `createday.sh daynumber` e.g. `createday.sh 02` . This will create a folder day02 with all example files, and update the build chain for the new day.
