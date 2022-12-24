add_library(day24 STATIC
    src/Day24.cpp
    src/Blizzard.cpp
)
target_include_directories(day24 BEFORE
    PUBLIC include
)
target_link_libraries(
  day24
  day
)

add_executable(
  day24_test
  tests/test.cpp
)

target_link_libraries(
  day24_test
  gtest gtest_main day24
)

include(GoogleTest)
gtest_discover_tests(day24_test)