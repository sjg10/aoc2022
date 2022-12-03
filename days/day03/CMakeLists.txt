add_library(day03 STATIC
    src/Day03.cpp
    src/Rucksacks.cpp
)
target_include_directories(day03 BEFORE
    PUBLIC include
)
target_link_libraries(
  day03
  day
)

add_executable(
  day03_test
  tests/test.cpp
)

target_link_libraries(
  day03_test
  gtest gtest_main day03
)

include(GoogleTest)
gtest_discover_tests(day03_test)