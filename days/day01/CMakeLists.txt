add_library(day01 STATIC
    src/Day01.cpp
)
target_include_directories(day01 BEFORE
    PUBLIC include
)
target_link_libraries(
  day01
  day
)

add_executable(
  day01_test
  tests/test.cpp
)

target_link_libraries(
  day01_test
  gtest gtest_main day01
)

include(GoogleTest)
gtest_discover_tests(day01_test)