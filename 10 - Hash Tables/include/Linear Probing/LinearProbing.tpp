#pragma once

template<typename K, typename V>
bool HashTableInsert(HashTable<K, V> &ht, const K &key, const V &value) {
    size_t index = HashFunction(key, ht.size);
    size_t count = 0;

    auto current = ht.bins[index];

    while (current != nullptr && current->key != key && count != ht.size) {
        index = index + 1;

        if (index >= ht.size)
            index = 0;

        current = ht.bins[index];
        count = count + 1;
    }

    if (count == ht.size)
        return false;

    if (current == nullptr) {
        ht.bins[index] = new HashTableEntry<K, V>(key, value);
        ht.num_keys = ht.num_keys + 1;
    } else {
        ht.bins[index]->value = value;
    }

    return true;
}

template<typename K, typename V>
std::optional<V> HashTableLookup(const HashTable<K, V> &ht, const K &key) {
    size_t index = HashFunction(key, ht.size);
    size_t count = 0;

    auto current = ht.bins[index];
    while (current != nullptr && current->key != key && count != ht.size) {
        index = index + 1;
        if (index >= ht.size)
            index = 0;
        current = ht.bins[index];
        count = count + 1;
    }

    // 返回找到的匹配值
    if (current != nullptr && current->key == key)
        return current->value;

    /* std::nullopt 是一个"空"的 optional，表示没有值
       可以用 if (result == std::nullopt)、if (result.has_value()) 或者 if (!result)
       来检查是否找到值
       可通过 result.value() 获取实际值（前提是确认它存在）
    */ 
    return std::nullopt;
}

template<typename K>
size_t HashFunction(const K &key, size_t size) noexcept {
    return std::hash<K>{}(key) % size;
}
