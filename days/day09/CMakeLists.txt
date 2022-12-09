add_library(day09 STATIC
    src/Day09.cpp
    src/Rope.cpp
)
target_include_directories(day09 BEFORE
    PUBLIC include
)
target_link_libraries(
  day09
  day
)

add_executable(
  day09_test
  tests/test.cpp
)

target_link_libraries(
  day09_test
  gtest gtest_main day09
)

include(GoogleTest)
gtest_discover_tests(day09_test)