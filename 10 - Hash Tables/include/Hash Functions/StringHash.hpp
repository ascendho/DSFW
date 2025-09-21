#pragma once

#include <string>

/*
    constexpr 类型的函数通常需要在头文件中定义，编译时求值需要
    constexpr 在编译时求值，零运行时开销
    const 在运行时求值，可能有开销
*/

// 质数因子
constexpr size_t CONST = 31;

constexpr size_t characterToNumber(char c) noexcept {
    // 类型转换操作符，常用&安全
    return static_cast<size_t>(c);
}

// StringHash 涉及动态内存分配以及参数 std::string 不是字面量类型，无法在编译时求值
size_t StringHash(const std::string &key, size_t size) noexcept;
