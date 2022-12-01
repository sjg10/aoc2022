add_library(day STATIC
    src/Day.cpp
)
target_include_directories(day BEFORE
    PUBLIC include
)