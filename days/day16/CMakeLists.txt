add_library(day16 STATIC
    src/Day16.cpp
    src/Volcano.cpp
)
target_include_directories(day16 BEFORE
    PUBLIC include
)
target_link_libraries(
  day16
  day
)

add_executable(
  day16_test
  tests/test.cpp
)

target_link_libraries(
  day16_test
  gtest gtest_main day16
)

include(GoogleTest)
gtest_discover_tests(day16_test)