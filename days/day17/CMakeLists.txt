add_library(day17 STATIC
    src/Day17.cpp
    src/RockSim.cpp
)
target_include_directories(day17 BEFORE
    PUBLIC include
)
target_link_libraries(
  day17
  day
)

add_executable(
  day17_test
  tests/test.cpp
)

target_link_libraries(
  day17_test
  gtest gtest_main day17
)

include(GoogleTest)
gtest_discover_tests(day17_test)