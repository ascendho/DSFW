#pragma once

#include "HashTable.hpp"

template<typename K, typename V>
bool HashTableInsert(HashTable<K, V> &ht, const K &key, const V &value);

template<typename K, typename V>
V HashTableLookup(HashTable<K, V> &ht, const K &key);

template<typename K>
size_t HashFunction(const K &key, size_t size) noexcept;

#include "LinearProbing.tpp"
