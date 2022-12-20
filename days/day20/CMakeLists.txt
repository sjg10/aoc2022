add_library(day20 STATIC
    src/Day20.cpp
    src/Messager.cpp
)
target_include_directories(day20 BEFORE
    PUBLIC include
)
target_link_libraries(
  day20
  day
)

add_executable(
  day20_test
  tests/test.cpp
)

target_link_libraries(
  day20_test
  gtest gtest_main day20
)

include(GoogleTest)
gtest_discover_tests(day20_test)