#pragma once
#include <string_view>

/*
 * 非拥有（non-owning）的字符串视图：
 * 1. 只是对现有字符串数据的引用
 * 2. 持有指向字符串数据的指针和字符串长度
 * 3. 不管理（不分配、不复制、不释放）字符串内存
 * 4. 只能读取，不能修改底层数据
 * 5. 零拷贝，非常轻量，开销成本极低
 *
 */

 // string_view 本身就是只读的，不需要额外的 const 保护
 // 同时字符串视图是轻量级对象，按值传递成本低，也更容易被编译器优化
bool StringEqual(std::string_view str1, std::string_view str2);