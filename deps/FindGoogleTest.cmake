include(FetchContent)

set(GoogleTest_version "1.11.0")

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-${GoogleTest_version}
)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  set(MESSAGE_QUIET ON)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
  unset(MESSAGE_QUIET)
endif()

find_package_handle_standard_args(GoogleTest
    VERSION_VAR GoogleTest_version
    REQUIRED_VARS googletest_BINARY_DIR)