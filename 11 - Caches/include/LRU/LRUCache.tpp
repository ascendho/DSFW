#pragma once

// 构造函数实现
template<typename K, typename V>
LRUCache<K, V>::LRUCache(size_t max_sz, std::function<V(const K&)> source) 
    : max_size(max_sz), current_size(0), data_source(source) {}

// 缓存查找函数实现
template<typename K, typename V>
V LRUCache<K, V>::CacheLookup(const K& key) {
    // 1. 在哈希表中查找缓存条目
    auto it = ht.find(key);
    CacheEntry<K, V>* entry = (it != ht.end()) ? &(it->second) : nullptr;
    
    if (entry == nullptr) {
        // 2. 如果缓存已满，需要移除最旧的条目
        if (current_size >= max_size) {
            auto key_to_remove_opt = Dequeue(q);
            if (key_to_remove_opt.has_value()) {
                K key_to_remove = key_to_remove_opt.value();
                ht.erase(key_to_remove);
                current_size = current_size - 1;
            }
        }
        
        // 3. 从慢速数据源获取数据
        V data = data_source(key);
        
        // 4. 将新键入队并创建缓存条目
        Enqueue(q, key);
        CacheEntry<K, V> new_entry(key, data, q.back);
        ht[key] = new_entry;
        current_size = current_size + 1;
        
        return data;
    } else {
        // 缓存命中：重置该键在队列中的位置
        // 移除旧节点
        RemoveNode(q, entry->node);
        
        // 重新入队
        Enqueue(q, key);
        
        // 更新缓存条目中的节点指针
        entry->node = q.back;
        
        return entry->value;
    }
}
