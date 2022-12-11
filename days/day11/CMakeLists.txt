add_library(day11 STATIC
    src/Day11.cpp
    src/Monkeys.cpp
)
target_include_directories(day11 BEFORE
    PUBLIC include
)
target_link_libraries(
  day11
  day
)

add_executable(
  day11_test
  tests/test.cpp
)

target_link_libraries(
  day11_test
  gtest gtest_main day11
)

include(GoogleTest)
gtest_discover_tests(day11_test)