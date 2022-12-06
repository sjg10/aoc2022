add_library(day06 STATIC
    src/Day06.cpp
)
target_include_directories(day06 BEFORE
    PUBLIC include
)
target_link_libraries(
  day06
  day
)

add_executable(
  day06_test
  tests/test.cpp
)

target_link_libraries(
  day06_test
  gtest gtest_main day06
)

include(GoogleTest)
gtest_discover_tests(day06_test)