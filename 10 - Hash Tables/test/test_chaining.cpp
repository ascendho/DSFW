#include "../src/Chaining.hpp"
#include <iostream>
#include <string>

int main() {
    using std::string;
    HashTable<string, int> ht(10);
    HashTableInsert(ht, string("apple"), 1);
    HashTableInsert(ht, string("banana"), 2);
    HashTableInsert(ht, string("cherry"), 3);

    auto node = HashTableLookUp(ht, string("banana"));
    if (node && node->value == 2)
        std::cout << "Test 1 passed: banana found" << std::endl;
    else
        std::cout << "Test 1 failed" << std::endl;

    HashTableInsert(ht, string("banana"), 5);
    node = HashTableLookUp(ht, string("banana"));
    if (node && node->value == 5)
        std::cout << "Test 2 passed: banana updated" << std::endl;
    else
        std::cout << "Test 2 failed" << std::endl;

    auto removed = HashTableRemove(ht, string("banana"));
    if (removed && removed->key == "banana") {
        std::cout << "Test 3 passed: banana removed" << std::endl;
        delete removed; // 释放被移除的节点
    } else
        std::cout << "Test 3 failed" << std::endl;

    node = HashTableLookUp(ht, string("banana"));
    if (!node)
        std::cout << "Test 4 passed: banana not found after removal" << std::endl;
    else
        std::cout << "Test 4 failed" << std::endl;

    // 边界测试：查找不存在的键
    node = HashTableLookUp(ht, string("not_exist"));
    if (!node)
        std::cout << "Test 5 passed: not_exist not found" << std::endl;
    else
        std::cout << "Test 5 failed" << std::endl;

    // 边界测试：删除不存在的键
    removed = HashTableRemove(ht, string("not_exist"));
    if (!removed)
        std::cout << "Test 6 passed: not_exist remove returns nullptr" << std::endl;
    else
        std::cout << "Test 6 failed" << std::endl;

    // 测试 int 类型键
    HashTable<int, string> ht2(10);
    HashTableInsert(ht2, 42, string("answer"));
    auto node2 = HashTableLookUp(ht2, 42);
    if (node2 && node2->value == "answer")
        std::cout << "Test 7 passed: int key found" << std::endl;
    else
        std::cout << "Test 7 failed" << std::endl;

    // 测试覆盖插入
    HashTableInsert(ht2, 42, string("new_answer"));
    node2 = HashTableLookUp(ht2, 42);
    if (node2 && node2->value == "new_answer")
        std::cout << "Test 8 passed: int key updated" << std::endl;
    else
        std::cout << "Test 8 failed" << std::endl;

    // 测试删除 int 键
    auto removed2 = HashTableRemove(ht2, 42);
    if (removed2 && removed2->key == 42) {
        std::cout << "Test 9 passed: int key removed" << std::endl;
        delete removed2; // 释放被移除的节点
    } else
        std::cout << "Test 9 failed" << std::endl;

    node2 = HashTableLookUp(ht2, 42);
    if (!node2)
        std::cout << "Test 10 passed: int key not found after removal" << std::endl;
    else
        std::cout << "Test 10 failed" << std::endl;

    return 0;
}
