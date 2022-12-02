add_library(day02 STATIC
    src/Day02.cpp
)
target_include_directories(day02 BEFORE
    PUBLIC include
)
target_link_libraries(
  day02
  day
)

add_executable(
  day02_test
  tests/test.cpp
)

target_link_libraries(
  day02_test
  gtest gtest_main day02
)

include(GoogleTest)
gtest_discover_tests(day02_test)