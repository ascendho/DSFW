cmake_minimum_required(VERSION 3.16)
project(10___Hash_Tables)

set(CMAKE_CXX_STANDARD 20)

# 确保 C++ 标准被严格要求
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 设置编译选项
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")
endif ()

# Google Test 支持
enable_testing()

# 查找系统安装的 Google Test
find_package(GTest REQUIRED)

# 包含目录
include_directories(include)

# 创建头文件列表（用于IDE显示，不参与编译）
set(HEADER_FILES
        include/Chaining/HashTable.hpp
        include/Chaining/Chaining.hpp
        include/Chaining/Chaining.tpp
        include/Linear\ Probing/HashTable.hpp
        include/Linear\ Probing/LinearProbing.hpp
        include/Linear\ Probing/LinearProbing.tpp
        include/Hash\ Functions/StringHash.hpp
)

# 源文件列表
set(SOURCE_FILES
        src/Hash\ Functions/StringHash.cpp
)

# Chaining 测试可执行文件
add_executable(test_chaining
        test/test_chaining.cpp
        ${HEADER_FILES}  # 添加头文件以便在IDE中显示
)

# 链接 Google Test
target_link_libraries(test_chaining GTest::gtest_main)

# 设置可执行文件输出目录
set_target_properties(test_chaining PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# 添加测试到 CTest
add_test(NAME HashTableTests COMMAND test_chaining)

# StringHash 测试可执行文件
add_executable(test_string_hash
        test/test_string_hash.cpp
        ${SOURCE_FILES}  # 包含源文件
        ${HEADER_FILES}  # 添加头文件以便在IDE中显示
)

# 链接 Google Test
target_link_libraries(test_string_hash GTest::gtest_main)

# 设置可执行文件输出目录
set_target_properties(test_string_hash PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# 添加测试到 CTest
add_test(NAME StringHashTests COMMAND test_string_hash)

# Linear Probing 测试可执行文件
add_executable(test_linear_probing
        test/test_linear_probing.cpp
        ${HEADER_FILES}  # 添加头文件以便在IDE中显示
)

# 链接 Google Test
target_link_libraries(test_linear_probing GTest::gtest_main)

# 设置可执行文件输出目录
set_target_properties(test_linear_probing PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# 添加测试到 CTest
add_test(NAME LinearProbingTests COMMAND test_linear_probing)


# 打印配置信息
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")
