#include <gtest/gtest.h>
#include "String Equal/StringEqual.hpp"

TEST(StringEqualTest, EqualStrings) {
    EXPECT_TRUE(StringEqual("", ""));
    EXPECT_TRUE(StringEqual("hello", "hello"));
}

TEST(StringEqualTest, DifferentStrings) {
    EXPECT_FALSE(StringEqual("hello", "world"));
    EXPECT_FALSE(StringEqual("abc", "ab"));
}
