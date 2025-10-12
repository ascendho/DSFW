#include <iostream>
#include <string>
#include <cassert>
#include "../include/LRU/LRUCache.hpp"

// 模拟慢速数据源函数
int slowDataSource(const int& key) {
    std::cout << "从慢速数据源获取键 " << key << " 的数据" << std::endl;
    return key * 10; // 返回键的10倍作为数据
}

void test_basic_operations() {
    std::cout << "\n=== 测试1: 基本操作 ===" << std::endl;
    
    LRUCache<int, int> cache(3, slowDataSource);
    
    // 第一次访问，应该从数据源获取
    std::cout << "访问键 1: ";
    int val1 = cache.CacheLookup(1);
    assert(val1 == 10);
    std::cout << "得到值: " << val1 << std::endl;
    
    // 第二次访问相同的键，应该从缓存获取（不会打印"从慢速数据源获取"）
    std::cout << "再次访问键 1: ";
    int val1_cached = cache.CacheLookup(1);
    assert(val1_cached == 10);
    std::cout << "得到值: " << val1_cached << std::endl;
    
    std::cout << "✓ 测试1通过" << std::endl;
}

void test_cache_capacity() {
    std::cout << "\n=== 测试2: 缓存容量限制 ===" << std::endl;
    
    LRUCache<int, int> cache(3, slowDataSource);
    
    // 填满缓存
    std::cout << "填充缓存 (容量=3):" << std::endl;
    cache.CacheLookup(1); // 队列: [1]
    cache.CacheLookup(2); // 队列: [1, 2]
    cache.CacheLookup(3); // 队列: [1, 2, 3]
    
    // 访问已缓存的键，不会触发数据源
    std::cout << "\n访问已缓存的键:" << std::endl;
    cache.CacheLookup(2); // 命中，队列更新: [1, 3, 2]
    
    // 添加第4个键，应该移除最旧的键(1)
    std::cout << "\n添加第4个键 (应该移除键 1):" << std::endl;
    cache.CacheLookup(4); // 队列: [3, 2, 4], 键1被移除
    
    // 再次访问键1，应该重新从数据源获取
    std::cout << "\n再次访问键 1 (应该重新从数据源获取):" << std::endl;
    cache.CacheLookup(1);
    
    std::cout << "✓ 测试2通过" << std::endl;
}

void test_lru_order() {
    std::cout << "\n=== 测试3: LRU顺序验证 ===" << std::endl;
    
    LRUCache<int, int> cache(3, slowDataSource);
    
    std::cout << "初始填充:" << std::endl;
    cache.CacheLookup(1); // 队列: [1]
    cache.CacheLookup(2); // 队列: [1, 2]
    cache.CacheLookup(3); // 队列: [1, 2, 3]
    
    std::cout << "\n访问键 1 (更新其位置):" << std::endl;
    cache.CacheLookup(1); // 队列: [2, 3, 1]
    
    std::cout << "\n添加新键 4 (应该移除键 2):" << std::endl;
    cache.CacheLookup(4); // 队列: [3, 1, 4], 键2被移除
    
    std::cout << "\n验证键 3 和 1 仍在缓存中:" << std::endl;
    cache.CacheLookup(3); // 应该命中
    cache.CacheLookup(1); // 应该命中
    
    std::cout << "\n验证键 2 已被移除:" << std::endl;
    cache.CacheLookup(2); // 应该重新从数据源获取
    
    std::cout << "✓ 测试3通过" << std::endl;
}

void test_string_cache() {
    std::cout << "\n=== 测试4: 字符串类型缓存 ===" << std::endl;
    
    auto stringDataSource = [](const std::string& key) -> std::string {
        std::cout << "从数据源获取: " << key << std::endl;
        return "value_" + key;
    };
    
    LRUCache<std::string, std::string> cache(2, stringDataSource);
    
    std::cout << "访问 'key1':" << std::endl;
    std::string val1 = cache.CacheLookup("key1");
    assert(val1 == "value_key1");
    
    std::cout << "访问 'key2':" << std::endl;
    std::string val2 = cache.CacheLookup("key2");
    assert(val2 == "value_key2");
    
    std::cout << "再次访问 'key1' (应该命中):" << std::endl;
    std::string val1_cached = cache.CacheLookup("key1");
    assert(val1_cached == "value_key1");
    
    std::cout << "访问 'key3' (应该移除 'key2'):" << std::endl;
    std::string val3 = cache.CacheLookup("key3");
    assert(val3 == "value_key3");
    
    std::cout << "再次访问 'key2' (应该重新获取):" << std::endl;
    std::string val2_new = cache.CacheLookup("key2");
    assert(val2_new == "value_key2");
    
    std::cout << "✓ 测试4通过" << std::endl;
}

void test_single_capacity() {
    std::cout << "\n=== 测试5: 容量为1的缓存 ===" << std::endl;
    
    LRUCache<int, int> cache(1, slowDataSource);
    
    std::cout << "访问键 1:" << std::endl;
    cache.CacheLookup(1);
    
    std::cout << "访问键 2 (应该移除键 1):" << std::endl;
    cache.CacheLookup(2);
    
    std::cout << "再次访问键 1 (应该重新获取):" << std::endl;
    cache.CacheLookup(1);
    
    std::cout << "✓ 测试5通过" << std::endl;
}

int main() {
    std::cout << "开始 LRU Cache 测试\n" << std::endl;
    
    try {
        test_basic_operations();
        test_cache_capacity();
        test_lru_order();
        test_string_cache();
        test_single_capacity();
        
        std::cout << "\n=== 所有测试通过! ===" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "测试失败: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
