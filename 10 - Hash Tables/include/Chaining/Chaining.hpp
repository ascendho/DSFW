/*
 * Include Guard 的作用：
 * 防止重复包含：确保头文件内容只被处理一次
 * 避免重复定义错误：防止类型、函数被多次定义
 * 提高编译效率：减少不必要的重复处理
 *
 */

#pragma once
#include "HashTable.hpp"

// 函数声明
template<typename K, typename V>
void HashTableInsert(HashTable<K, V> &ht, const K &key, const V &value);

template<typename K, typename V>
ListNode<K, V> *HashTableLookup(const HashTable<K, V> &ht, const K &key);

template<typename K, typename V>
ListNode<K, V> *HashTableRemove(HashTable<K, V> &ht, const K &key);

template<typename K>
size_t HashFunction(const K &key, size_t size) noexcept;

// 包含模板实现
#include "Chaining.tpp"
