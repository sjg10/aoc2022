add_library(day10 STATIC
    src/Day10.cpp
    src/CPU.cpp
)
target_include_directories(day10 BEFORE
    PUBLIC include
)
target_link_libraries(
  day10
  day
)

add_executable(
  day10_test
  tests/test.cpp
)

target_link_libraries(
  day10_test
  gtest gtest_main day10
)

include(GoogleTest)
gtest_discover_tests(day10_test)