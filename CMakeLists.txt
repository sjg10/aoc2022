cmake_minimum_required(VERSION 3.14)
project(aoc2022)

# Get deps folder
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/deps/)

# Setup Compiler
set(CMAKE_CXX_STANDARD 20)
add_compile_options(-Wall -Wextra -Wpedantic -Werror)


# enable tests
include(CTest)
enable_testing()
find_package(GoogleTest REQUIRED)
find_package(jsoncpp REQUIRED)

# Add subdirectories
add_subdirectory(days)
add_subdirectory(common)

# Add main executable
add_executable(aoc2022
    aoc2022.cpp)
target_link_libraries(
    aoc2022
    day01
    day02
    day03
    day04
    day05
    day06
    day07
    day08
    day09
    day10
    day11
    day12
    day13
    day14
    day15
    day16
    day17
    day18
    day19
    day20
    day21
    day22
    day23
    # Further days go here
)