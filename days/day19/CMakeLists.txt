add_library(day19 STATIC
    src/Day19.cpp
    src/GeodeFactory.cpp
)
target_include_directories(day19 BEFORE
    PUBLIC include
)
target_link_libraries(
  day19
  day
)

add_executable(
  day19_test
  tests/test.cpp
)

target_link_libraries(
  day19_test
  gtest gtest_main day19
)

include(GoogleTest)
gtest_discover_tests(day19_test)