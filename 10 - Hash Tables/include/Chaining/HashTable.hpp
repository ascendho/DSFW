#pragma once

#include <vector>

template<typename K, typename V>
struct ListNode {
    K key;
    V value;
    ListNode *next;


    [[nodiscard]] ListNode(const K &key, const V &value)
        : key(key),
          value(value), next(nullptr) {
    }
};

template<typename K, typename V>
class HashTable {
public:
    size_t size;
    std::vector<ListNode<K, V> *> bins;

    explicit HashTable(size_t table_size) : size(table_size), bins(table_size, nullptr) {
    }

    // 析构函数：清理所有链表节点
    ~HashTable() {
        for (auto &head: bins) {
            while (head != nullptr) {
                ListNode<K, V> *temp = head;
                head = head->next;
                delete temp;
            }
        }
    }
};

// using keyword
