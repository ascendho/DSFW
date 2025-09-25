#pragma once
#include <vector>

template<typename T>

/*
 * 概念约束，要求 T 必须支持完全排序：
 * 编译时错误监测
 * 更好的错误信息
 * 类型安全机制
 *
 */
 
requires std::totally_ordered<T>
void InsertionSort(std::vector<T>& A);

#include "Insertion Sort.tpp"