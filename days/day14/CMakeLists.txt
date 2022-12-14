add_library(day14 STATIC
    src/Day14.cpp
    src/Cave.cpp
)
target_include_directories(day14 BEFORE
    PUBLIC include
)
target_link_libraries(
  day14
  day
)

add_executable(
  day14_test
  tests/test.cpp
)

target_link_libraries(
  day14_test
  gtest gtest_main day14
)

include(GoogleTest)
gtest_discover_tests(day14_test)