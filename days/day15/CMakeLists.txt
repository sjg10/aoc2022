add_library(day15 STATIC
    src/Day15.cpp
    src/BeaconMap.cpp
)
target_include_directories(day15 BEFORE
    PUBLIC include
)
target_link_libraries(
  day15
  pthread
  day
)

add_executable(
  day15_test
  tests/test.cpp
)

target_link_libraries(
  day15_test
  gtest gtest_main day15
)

include(GoogleTest)
gtest_discover_tests(day15_test)