#include <gtest/gtest.h>
#include "../include/Chaining/Chaining.hpp"
#include <string>

class HashTableTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 每个测试前都会运行
    }

    void TearDown() override {
        // 每个测试后都会运行
    }
};

// 测试用例类：字符串键和整数值
class StringIntHashTableTest : public HashTableTest {
protected:
    void SetUp() override {
        HashTableTest::SetUp();
        ht = std::make_unique<HashTable<std::string, int> >(10);
        HashTableInsert(*ht, std::string("apple"), 1);
        HashTableInsert(*ht, std::string("banana"), 2);
        HashTableInsert(*ht, std::string("cherry"), 3);
    }

    std::unique_ptr<HashTable<std::string, int> > ht;
};

// 测试用例类：整数键和字符串值
class IntStringHashTableTest : public HashTableTest {
protected:
    void SetUp() override {
        HashTableTest::SetUp();
        ht = std::make_unique<HashTable<int, std::string> >(10);
    }

    std::unique_ptr<HashTable<int, std::string> > ht;
};

// 基本插入和查找测试
TEST_F(StringIntHashTableTest, BasicLookup) {
    auto node = HashTableLookup(*ht, std::string("banana"));
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->value, 2);
}

// 更新现有键的值
TEST_F(StringIntHashTableTest, UpdateExistingKey) {
    HashTableInsert(*ht, std::string("banana"), 5);
    auto node = HashTableLookup(*ht, std::string("banana"));
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->value, 5);
}

// 移除键值对
TEST_F(StringIntHashTableTest, RemoveKey) {
    auto removed = HashTableRemove(*ht, std::string("banana"));
    ASSERT_NE(removed, nullptr);
    EXPECT_EQ(removed->key, "banana");
    EXPECT_EQ(removed->value, 2);
    delete removed; // 清理内存
}

// 移除后查找应返回nullptr
TEST_F(StringIntHashTableTest, LookupAfterRemoval) {
    auto removed = HashTableRemove(*ht, std::string("banana"));
    ASSERT_NE(removed, nullptr);
    delete removed; // 清理内存

    auto node = HashTableLookup(*ht, std::string("banana"));
    EXPECT_EQ(node, nullptr);
}

// 查找不存在的键
TEST_F(StringIntHashTableTest, LookupNonExistentKey) {
    auto node = HashTableLookup(*ht, std::string("not_exist"));
    EXPECT_EQ(node, nullptr);
}

// 删除不存在的键
TEST_F(StringIntHashTableTest, RemoveNonExistentKey) {
    auto removed = HashTableRemove(*ht, std::string("not_exist"));
    EXPECT_EQ(removed, nullptr);
}

// 测试整数键类型
TEST_F(IntStringHashTableTest, IntegerKeyOperations) {
    HashTableInsert(*ht, 42, std::string("answer"));

    auto node = HashTableLookup(*ht, 42);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->value, "answer");
}

// 测试整数键的更新
TEST_F(IntStringHashTableTest, UpdateIntegerKey) {
    HashTableInsert(*ht, 42, std::string("answer"));
    HashTableInsert(*ht, 42, std::string("new_answer"));

    auto node = HashTableLookup(*ht, 42);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->value, "new_answer");
}

// 测试整数键的删除
TEST_F(IntStringHashTableTest, RemoveIntegerKey) {
    HashTableInsert(*ht, 42, std::string("answer"));

    auto removed = HashTableRemove(*ht, 42);
    ASSERT_NE(removed, nullptr);
    EXPECT_EQ(removed->key, 42);
    EXPECT_EQ(removed->value, "answer");
    delete removed; // 清理内存

    auto node = HashTableLookup(*ht, 42);
    EXPECT_EQ(node, nullptr);
}

// 测试空哈希表
TEST_F(HashTableTest, EmptyHashTable) {
    HashTable<std::string, int> empty_ht(5);

    auto node = HashTableLookup(empty_ht, std::string("anything"));
    EXPECT_EQ(node, nullptr);

    auto removed = HashTableRemove(empty_ht, std::string("anything"));
    EXPECT_EQ(removed, nullptr);
}

// 测试多次插入和删除
TEST_F(StringIntHashTableTest, MultipleInsertionsAndDeletions) {
    // 添加更多元素
    HashTableInsert(*ht, std::string("date"), 4);
    HashTableInsert(*ht, std::string("elderberry"), 5);

    // 验证所有元素都存在
    EXPECT_NE(HashTableLookup(*ht, std::string("apple")), nullptr);
    EXPECT_NE(HashTableLookup(*ht, std::string("banana")), nullptr);
    EXPECT_NE(HashTableLookup(*ht, std::string("cherry")), nullptr);
    EXPECT_NE(HashTableLookup(*ht, std::string("date")), nullptr);
    EXPECT_NE(HashTableLookup(*ht, std::string("elderberry")), nullptr);

    // 删除几个元素
    auto removed1 = HashTableRemove(*ht, std::string("apple"));
    auto removed2 = HashTableRemove(*ht, std::string("cherry"));

    ASSERT_NE(removed1, nullptr);
    ASSERT_NE(removed2, nullptr);
    delete removed1;
    delete removed2;

    // 验证删除的元素不存在，剩余元素仍存在
    EXPECT_EQ(HashTableLookup(*ht, std::string("apple")), nullptr);
    EXPECT_EQ(HashTableLookup(*ht, std::string("cherry")), nullptr);
    EXPECT_NE(HashTableLookup(*ht, std::string("banana")), nullptr);
    EXPECT_NE(HashTableLookup(*ht, std::string("date")), nullptr);
    EXPECT_NE(HashTableLookup(*ht, std::string("elderberry")), nullptr);
}
