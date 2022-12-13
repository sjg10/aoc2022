add_library(day13 STATIC
    src/Day13.cpp
    src/Message.cpp
)
target_include_directories(day13 BEFORE
    PUBLIC include
)
target_link_libraries(
  day13
  day
  jsoncpp_lib
)

add_executable(
  day13_test
  tests/test.cpp
)

target_link_libraries(
  day13_test
  gtest gtest_main day13
)

include(GoogleTest)
gtest_discover_tests(day13_test)