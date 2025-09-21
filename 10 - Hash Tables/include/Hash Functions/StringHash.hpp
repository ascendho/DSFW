#pragma once

#include <string>

// constexpr 与 const
// 质数因子
constexpr size_t CONST = 31;

// constexpr 类型的函数通常需要在头文件中定义，编译时求值需要
constexpr size_t characterToNumber(char c) noexcept {
    // 类型转换操作符，常用&安全
    return static_cast<size_t>(c);
}

size_t StringHash(const std::string &key, size_t size) noexcept;
