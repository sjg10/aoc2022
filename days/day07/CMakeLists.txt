add_library(day07 STATIC
    src/Day07.cpp
    src/Directories.cpp
)
target_include_directories(day07 BEFORE
    PUBLIC include
)
target_link_libraries(
  day07
  day
)

add_executable(
  day07_test
  tests/test.cpp
)

target_link_libraries(
  day07_test
  gtest gtest_main day07
)

include(GoogleTest)
gtest_discover_tests(day07_test)