#include <gtest/gtest.h>
#include "Day25.h"
// Demonstrate some basic assertions for new class.
TEST(Day25Test, Part1Part2) {
    ASSERT_EQ(Day25::snafuToInt("1=-0-2"),     1747);
    ASSERT_EQ(Day25::snafuToInt("12111"),      906);
    ASSERT_EQ(Day25::snafuToInt("2=0="),      198);
    ASSERT_EQ(Day25::snafuToInt("21"),       11);
    ASSERT_EQ(Day25::snafuToInt("2=01"),      201);
    ASSERT_EQ(Day25::snafuToInt("111"),       31);
    ASSERT_EQ(Day25::snafuToInt("20012"),     1257);
    ASSERT_EQ(Day25::snafuToInt("112"),       32);
    ASSERT_EQ(Day25::snafuToInt("1=-1="),      353);
    ASSERT_EQ(Day25::snafuToInt("1-12"),      107);
    ASSERT_EQ(Day25::snafuToInt("12"),        7);
    ASSERT_EQ(Day25::snafuToInt("1="),        3);
    ASSERT_EQ(Day25::snafuToInt("122"),       37);
ASSERT_EQ(Day25::IntToSnafu(        1),  "1");
ASSERT_EQ(Day25::IntToSnafu(        2),  "2");
ASSERT_EQ(Day25::IntToSnafu(        3),  "1=");
ASSERT_EQ(Day25::IntToSnafu(        4),  "1-");
ASSERT_EQ(Day25::IntToSnafu(        5),  "10");
ASSERT_EQ(Day25::IntToSnafu(        6),  "11");
ASSERT_EQ(Day25::IntToSnafu(        7),  "12");
ASSERT_EQ(Day25::IntToSnafu(        8),  "2=");
ASSERT_EQ(Day25::IntToSnafu(        9),  "2-");
ASSERT_EQ(Day25::IntToSnafu(       10),  "20");
ASSERT_EQ(Day25::IntToSnafu(       15),  "1=0");
ASSERT_EQ(Day25::IntToSnafu(       20),  "1-0");
ASSERT_EQ(Day25::IntToSnafu(     2022),  "1=11-2");
ASSERT_EQ(Day25::IntToSnafu(    12345),  "1-0---0");
ASSERT_EQ(Day25::IntToSnafu(314159265),  "1121-1110-1=0");
}
