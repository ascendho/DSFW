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
V HashTableLookup(HashTable<K, V> &ht, const K &key) {
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

    // 伪代码中返回null，这里返回默认值
    return V{};
}

template<typename K>
size_t HashFunction(const K &key, size_t size) noexcept {
    return std::hash<K>{}(key) % size;
}
