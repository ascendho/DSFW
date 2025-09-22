#pragma once

#include <vector>

template<typename K, typename V>
struct HashTableEntry {
    K key;
    V value;

    HashTableEntry(const K &key, const V &value)
        : key(key), value(value) {
    }
};

template<typename K, typename V>
class HashTable {
public:
    // 公共接口成员 - 需要被外部函数访问
    size_t size;
    size_t num_keys;
    std::vector<HashTableEntry<K, V> *> bins;

    // 添加构造函数
    // explicit 关键字防止隐式转换，单参数构造函数几乎总是应该使用它
    // 例如，有了 explicit 关键字，HashTable<int> ht = 10; 这样的代码就会报错，防止从数字意外创建哈希表
    explicit HashTable(size_t initial_size)
        : size(initial_size), num_keys(0), bins(initial_size, nullptr) {
    }

    // 析构函数：清理内存
    ~HashTable() {
        for (auto *entry: bins) {
            delete entry;
        }
    }
};
