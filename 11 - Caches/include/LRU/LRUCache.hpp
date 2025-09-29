#pragma once

#include <unordered_map>

#include "queue.hpp"



template<typename K, typename V>
struct CacheEntry {
    K key;
    V value;
    QueueListNode<K>* node;
};


template<typename K, typename V>
struct LRUCache {
    std::unordered_map<K, CacheEntry<K,V>> ht;
    Queue<K> q;
    size_t max_size;
    size_t current_size;
};