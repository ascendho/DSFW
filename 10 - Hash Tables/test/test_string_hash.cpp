#include <gtest/gtest.h>
#include "../include/Hash Functions/StringHash.hpp"
#include <string>
#include <unordered_set>
#include <vector>
#include <algorithm>

class StringHashTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 每个测试前都会运行
    }

    void TearDown() override {
        // 每个测试后都会运行
    }
};

// 测试 characterToNumber 函数
TEST_F(StringHashTest, CharacterToNumberTest) {
    // 测试基本字符
    EXPECT_EQ(characterToNumber('a'), static_cast<size_t>('a'));
    EXPECT_EQ(characterToNumber('A'), static_cast<size_t>('A'));
    EXPECT_EQ(characterToNumber('0'), static_cast<size_t>('0'));
    EXPECT_EQ(characterToNumber('9'), static_cast<size_t>('9'));

    // 测试特殊字符
    EXPECT_EQ(characterToNumber(' '), static_cast<size_t>(' '));
    EXPECT_EQ(characterToNumber('!'), static_cast<size_t>('!'));
    EXPECT_EQ(characterToNumber('@'), static_cast<size_t>('@'));

    // 验证函数是 constexpr 和 noexcept
    static_assert(characterToNumber('x') == static_cast<size_t>('x'), "Should be constexpr");
    EXPECT_TRUE(noexcept(characterToNumber('x')));
}

// 测试 StringHash 函数的基本功能
TEST_F(StringHashTest, BasicStringHashTest) {
    const int table_size = 100;

    // 测试空字符串
    size_t hash_empty = StringHash("", table_size);
    EXPECT_LT(hash_empty, table_size);
    EXPECT_EQ(hash_empty, 0); // 空字符串的哈希值应该是0

    // 测试单字符字符串
    size_t hash_a = StringHash("a", table_size);
    EXPECT_LT(hash_a, table_size);
    EXPECT_EQ(hash_a, static_cast<size_t>('a') % table_size);

    // 测试多字符字符串
    size_t hash_hello = StringHash("hello", table_size);
    EXPECT_LT(hash_hello, table_size);
}

// 测试哈希函数的一致性
TEST_F(StringHashTest, ConsistencyTest) {
    const int table_size = 1000;
    std::string test_string = "test_string_123";

    // 多次调用应该返回相同的结果
    size_t hash1 = StringHash(test_string, table_size);
    size_t hash2 = StringHash(test_string, table_size);
    size_t hash3 = StringHash(test_string, table_size);

    EXPECT_EQ(hash1, hash2);
    EXPECT_EQ(hash2, hash3);
}

// 测试不同字符串产生不同的哈希值（大部分情况下）
TEST_F(StringHashTest, DistinctHashValuesTest) {
    const int table_size = 10000;
    std::vector<std::string> test_strings = {
        "apple", "banana", "cherry", "date", "elderberry",
        "fig", "grape", "honeydew", "kiwi", "lemon",
        "mango", "nectarine", "orange", "papaya", "quince"
    };

    std::unordered_set<size_t> hash_values;

    for (const auto &str: test_strings) {
        size_t hash_val = StringHash(str, table_size);
        EXPECT_LT(hash_val, table_size);
        hash_values.insert(hash_val);
    }

    // 大部分字符串应该产生不同的哈希值
    // 允许少量碰撞，但不应该所有都相同
    EXPECT_GT(hash_values.size(), test_strings.size() / 2);
}

// 测试边界情况
TEST_F(StringHashTest, BoundaryTest) {
    // 测试最小表大小
    EXPECT_EQ(StringHash("test", 1), 0);

    // 测试较大的表大小
    const int large_size = 999999;
    size_t hash_large = StringHash("test_large_table", large_size);
    EXPECT_LT(hash_large, large_size);
}

// 测试特殊字符
TEST_F(StringHashTest, SpecialCharactersTest) {
    const int table_size = 100;

    std::vector<std::string> special_strings = {
        "hello world", // 空格
        "test@email.com", // 特殊符号
        "123456", // 数字
        "Mixed123!@#", // 混合字符
        "测试中文", // 如果支持Unicode
        "" // 空字符串
    };

    for (const auto &str: special_strings) {
        size_t hash_val = StringHash(str, table_size);
        EXPECT_LT(hash_val, table_size);
        EXPECT_GE(hash_val, 0);
    }
}

// 测试哈希分布性
TEST_F(StringHashTest, DistributionTest) {
    const int table_size = 100;
    const int num_buckets = 10;
    std::vector<int> bucket_counts(num_buckets, 0);

    // 生成测试字符串
    std::vector<std::string> test_strings;
    for (int i = 0; i < 1000; ++i) {
        test_strings.push_back("test_string_" + std::to_string(i));
    }

    // 计算哈希值并分桶
    for (const auto &str: test_strings) {
        size_t hash_val = StringHash(str, table_size);
        int bucket = (hash_val * num_buckets) / table_size;
        bucket_counts[bucket]++;
    }

    // 检查分布是否相对均匀（没有桶完全为空）
    for (int count: bucket_counts) {
        EXPECT_GT(count, 0); // 每个桶都应该有一些元素
    }

    // 检查是否没有某个桶占据了过多的元素
    int max_count = *std::max_element(bucket_counts.begin(), bucket_counts.end());
    int min_count = *std::min_element(bucket_counts.begin(), bucket_counts.end());

    // 最大桶和最小桶的差距不应该太大
    EXPECT_LT(max_count, min_count * 3);
}

// 测试 noexcept 规范
TEST_F(StringHashTest, NoexceptTest) {
    std::string test_str = "test";
    EXPECT_TRUE(noexcept(StringHash(test_str, 100)));
    EXPECT_TRUE(noexcept(characterToNumber('a')));
}
