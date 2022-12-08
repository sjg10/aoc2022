add_library(day08 STATIC
    src/Day08.cpp
)
target_include_directories(day08 BEFORE
    PUBLIC include
)
target_link_libraries(
  day08
  day
)

add_executable(
  day08_test
  tests/test.cpp
)

target_link_libraries(
  day08_test
  gtest gtest_main day08
)

include(GoogleTest)
gtest_discover_tests(day08_test)