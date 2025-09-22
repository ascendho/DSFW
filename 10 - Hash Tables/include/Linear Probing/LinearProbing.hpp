#pragma once

#include "HashTable.hpp"
#include <optional>

template<typename K, typename V>
bool HashTableInsert(HashTable<K, V> &ht, const K &key, const V &value);

/* std::optional 用于表示可能存在也可能不存在的值
   适用于查找操作，明确区分 "找到"和 "未找到"
   避免使用特殊值（如 nullptr 或 -1）来表示未找到，提升代码可读性和安全性
*/
template<typename K, typename V>
std::optional<V> HashTableLookup(const HashTable<K, V> &ht, const K &key);

template<typename K>
size_t HashFunction(const K &key, size_t size) noexcept;

#include "LinearProbing.tpp"
