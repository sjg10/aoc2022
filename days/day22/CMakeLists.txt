add_library(day22 STATIC
    src/Day22.cpp
    src/MonkeyMap.cpp
)
target_include_directories(day22 BEFORE
    PUBLIC include
)
target_link_libraries(
  day22
  day
)

add_executable(
  day22_test
  tests/test.cpp
)

target_link_libraries(
  day22_test
  gtest gtest_main day22
)

include(GoogleTest)
gtest_discover_tests(day22_test)