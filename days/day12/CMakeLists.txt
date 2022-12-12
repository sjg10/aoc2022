add_library(day12 STATIC
    src/Day12.cpp
    src/Map.cpp
)
target_include_directories(day12 BEFORE
    PUBLIC include
)
target_link_libraries(
  day12
  day
)

add_executable(
  day12_test
  tests/test.cpp
)

target_link_libraries(
  day12_test
  gtest gtest_main day12
)

include(GoogleTest)
gtest_discover_tests(day12_test)