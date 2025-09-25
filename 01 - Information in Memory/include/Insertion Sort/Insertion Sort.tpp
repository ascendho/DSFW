#pragma once

#include <concepts>

template<typename T>
/*
 * 概念约束，要求 T 必须支持完全排序：
 * 编译时错误监测
 * 更好的错误信息
 * 类型安全机制
 *
 */ 
requires std::totally_ordered<T>
void InsertionSort(std::vector<T> &A) {
    size_t N = A.size();
    int i = 1;

    while (i < N) {
        auto current = A[i];
        size_t j = i - 1;

        while (j < N && A[j] > current) {
            A[j + 1] = A[j];
            j = j - 1;
        }
        A[j + 1] = current;
        i = i + 1;
    }
}
