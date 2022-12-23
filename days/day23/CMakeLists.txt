add_library(day23 STATIC
    src/Day23.cpp
    src/ElfMap.cpp
)
target_include_directories(day23 BEFORE
    PUBLIC include
)
target_link_libraries(
  day23
  day
)

add_executable(
  day23_test
  tests/test.cpp
)

target_link_libraries(
  day23_test
  gtest gtest_main day23
)

include(GoogleTest)
gtest_discover_tests(day23_test)