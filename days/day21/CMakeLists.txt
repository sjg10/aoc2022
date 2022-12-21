add_library(day21 STATIC
    src/Day21.cpp
    src/MonkeyMaths.cpp
)
target_include_directories(day21 BEFORE
    PUBLIC include
)
target_link_libraries(
  day21
  day
)

add_executable(
  day21_test
  tests/test.cpp
)

target_link_libraries(
  day21_test
  gtest gtest_main day21
)

include(GoogleTest)
gtest_discover_tests(day21_test)