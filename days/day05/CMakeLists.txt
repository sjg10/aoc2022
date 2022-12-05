add_library(day05 STATIC
    src/Day05.cpp
)
target_include_directories(day05 BEFORE
    PUBLIC include
)
target_link_libraries(
  day05
  day
)

add_executable(
  day05_test
  tests/test.cpp
)

target_link_libraries(
  day05_test
  gtest gtest_main day05
)

include(GoogleTest)
gtest_discover_tests(day05_test)