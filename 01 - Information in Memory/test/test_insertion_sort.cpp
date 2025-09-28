#include <gtest/gtest.h>
#include <vector>
#include "Insertion Sort/Insertion Sort.hpp"

TEST(InsertionSortTest, SortsIntegerVector) {
    std::vector<int> v{5, 2, 9, 1, 5, 6};
    InsertionSort(v);
    ASSERT_EQ(v.size(), 6);
    for (size_t i = 1; i < v.size(); ++i) {
        EXPECT_LE(v[i-1], v[i]);
    }
}

TEST(InsertionSortTest, HandlesEmpty) {
    std::vector<int> v{};
    InsertionSort(v);
    EXPECT_TRUE(v.empty());
}
