add_library(day18 STATIC
    src/Day18.cpp
    src/CubeMap.cpp
)
target_include_directories(day18 BEFORE
    PUBLIC include
)
target_link_libraries(
  day18
  day
)

add_executable(
  day18_test
  tests/test.cpp
)

target_link_libraries(
  day18_test
  gtest gtest_main day18
)

include(GoogleTest)
gtest_discover_tests(day18_test)