add_library(day04 STATIC
    src/Day04.cpp
)
target_include_directories(day04 BEFORE
    PUBLIC include
)
target_link_libraries(
  day04
  day
)

add_executable(
  day04_test
  tests/test.cpp
)

target_link_libraries(
  day04_test
  gtest gtest_main day04
)

include(GoogleTest)
gtest_discover_tests(day04_test)