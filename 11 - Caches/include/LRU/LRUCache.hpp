#pragma once

#include <unordered_map>
#include <functional>
#include "../Queue/queue.hpp"

template<typename K, typename V>
struct CacheEntry {
    K key;
    V value;
    QueueListNode<K>* node;
    
    CacheEntry() : key(K()), value(V()), node(nullptr) {}
    CacheEntry(const K& k, const V& v, QueueListNode<K>* n) 
        : key(k), value(v), node(n) {}
};

template<typename K, typename V>
class LRUCache {
private:
    std::unordered_map<K, CacheEntry<K, V>> ht;
    Queue<K> q;
    size_t max_size;
    size_t current_size;

    // 慢速数据源
    std::function<V(const K&)> data_source;

public:
    // 构造函数
    LRUCache(size_t max_sz, std::function<V(const K&)> source);
    
    // 缓存查找函数
    V CacheLookup(const K& key);
};

#include "LRUCache.tpp"