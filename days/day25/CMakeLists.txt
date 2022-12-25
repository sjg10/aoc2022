add_library(day25 STATIC
    src/Day25.cpp
)
target_include_directories(day25 BEFORE
    PUBLIC include
)
target_link_libraries(
  day25
  day
)

add_executable(
  day25_test
  tests/test.cpp
)

target_link_libraries(
  day25_test
  gtest gtest_main day25
)

include(GoogleTest)
gtest_discover_tests(day25_test)