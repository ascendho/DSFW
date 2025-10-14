#include <gtest/gtest.h>
#include "../include/LRU/LRUCache.hpp"
#include <string>

class LRUCacheTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 每个测试前都会运行
    }

    void TearDown() override {
        // 每个测试后都会运行
    }

    // 模拟慢速数据源函数
    static int slowDataSource(const int& key) {
        return key * 10; // 返回键的10倍作为数据
    }
};

// 测试用例类：整数键和整数值
class IntIntCacheTest : public LRUCacheTest {
protected:
    void SetUp() override {
        LRUCacheTest::SetUp();
        cache = std::make_unique<LRUCache<int, int>>(3, slowDataSource);
    }

    std::unique_ptr<LRUCache<int, int>> cache;
};

// 测试用例类：字符串键和字符串值
class StringStringCacheTest : public LRUCacheTest {
protected:
    void SetUp() override {
        LRUCacheTest::SetUp();
        stringDataSource = [](const std::string& key) -> std::string {
            return "value_" + key;
        };
        cache = std::make_unique<LRUCache<std::string, std::string>>(2, stringDataSource);
    }

    std::function<std::string(const std::string&)> stringDataSource;
    std::unique_ptr<LRUCache<std::string, std::string>> cache;
};

// 基本操作测试
TEST_F(IntIntCacheTest, BasicLookup) {
    int val1 = cache->CacheLookup(1);
    EXPECT_EQ(val1, 10);
    
    // 第二次访问相同的键，应该从缓存获取
    int val1_cached = cache->CacheLookup(1);
    EXPECT_EQ(val1_cached, 10);
}

// 测试缓存容量限制
TEST_F(IntIntCacheTest, CacheCapacity) {
    // 填满缓存
    cache->CacheLookup(1); // 队列: [1]
    cache->CacheLookup(2); // 队列: [1, 2]
    cache->CacheLookup(3); // 队列: [1, 2, 3]
    
    // 访问已缓存的键
    cache->CacheLookup(2); // 命中，队列更新: [1, 3, 2]
    
    // 添加第4个键，应该移除最旧的键(1)
    cache->CacheLookup(4); // 队列: [3, 2, 4], 键1被移除
    
    // 验证功能正常
    int val4 = cache->CacheLookup(4);
    EXPECT_EQ(val4, 40);
}

// LRU顺序验证
TEST_F(IntIntCacheTest, LRUOrder) {
    cache->CacheLookup(1); // 队列: [1]
    cache->CacheLookup(2); // 队列: [1, 2]
    cache->CacheLookup(3); // 队列: [1, 2, 3]
    
    // 访问键 1，更新其位置
    int val1 = cache->CacheLookup(1); // 队列: [2, 3, 1]
    EXPECT_EQ(val1, 10);
    
    // 添加新键 4，应该移除键 2
    cache->CacheLookup(4); // 队列: [3, 1, 4], 键2被移除
    
    // 验证键 3 和 1 仍在缓存中
    int val3 = cache->CacheLookup(3);
    EXPECT_EQ(val3, 30);
    
    int val1_again = cache->CacheLookup(1);
    EXPECT_EQ(val1_again, 10);
}

// 字符串类型缓存测试
TEST_F(StringStringCacheTest, StringCache) {
    std::string val1 = cache->CacheLookup("key1");
    EXPECT_EQ(val1, "value_key1");
    
    std::string val2 = cache->CacheLookup("key2");
    EXPECT_EQ(val2, "value_key2");
    
    // 再次访问 key1，应该命中
    std::string val1_cached = cache->CacheLookup("key1");
    EXPECT_EQ(val1_cached, "value_key1");
    
    // 访问 key3，应该移除 key2
    std::string val3 = cache->CacheLookup("key3");
    EXPECT_EQ(val3, "value_key3");
}

// 字符串缓存更新测试
TEST_F(StringStringCacheTest, StringCacheEviction) {
    cache->CacheLookup("key1");
    cache->CacheLookup("key2");
    cache->CacheLookup("key1"); // key1 更新到最新
    
    // 添加 key3，应该移除 key2
    cache->CacheLookup("key3");
    
    // 再次访问 key2，应该重新从数据源获取
    std::string val2_new = cache->CacheLookup("key2");
    EXPECT_EQ(val2_new, "value_key2");
}

// 容量为1的缓存测试
TEST_F(LRUCacheTest, SingleCapacity) {
    LRUCache<int, int> single_cache(1, slowDataSource);
    
    single_cache.CacheLookup(1);
    
    // 访问键 2，应该移除键 1
    int val2 = single_cache.CacheLookup(2);
    EXPECT_EQ(val2, 20);
    
    // 再次访问键 1，应该重新获取
    int val1 = single_cache.CacheLookup(1);
    EXPECT_EQ(val1, 10);
}

// 空缓存测试
TEST_F(LRUCacheTest, EmptyCache) {
    LRUCache<int, int> empty_cache(5, slowDataSource);
    
    // 第一次访问应该正常工作
    int val = empty_cache.CacheLookup(42);
    EXPECT_EQ(val, 420);
}

// 多次插入和访问测试
TEST_F(IntIntCacheTest, MultipleInsertionsAndAccess) {
    // 添加多个元素
    cache->CacheLookup(1);
    cache->CacheLookup(2);
    cache->CacheLookup(3);
    
    // 验证所有元素都存在
    EXPECT_EQ(cache->CacheLookup(1), 10);
    EXPECT_EQ(cache->CacheLookup(2), 20);
    EXPECT_EQ(cache->CacheLookup(3), 30);
    
    // 添加新元素，触发淘汰
    cache->CacheLookup(4);
    cache->CacheLookup(5);
    
    // 验证功能正常
    EXPECT_EQ(cache->CacheLookup(5), 50);
}
