cmake_minimum_required(VERSION 4.0)
project(10___Hash_Tables)

set(CMAKE_CXX_STANDARD 20)

# 确保 C++ 标准被严格要求
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 设置编译选项
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")
endif()

# 包含目录
include_directories(src)

# 创建头文件列表（用于IDE显示，不参与编译）
set(HEADER_FILES
    src/HashTable.hpp
    src/Chaining.hpp
    src/Chaining.tpp
)

# 测试可执行文件
add_executable(test_chaining
        test/test_chaining.cpp
    ${HEADER_FILES}  # 添加头文件以便在IDE中显示
)

# 设置可执行文件输出目录
set_target_properties(test_chaining PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# 启用测试
enable_testing()

# 添加测试
add_test(NAME hash_table_basic_test 
         COMMAND test_chaining
         WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 创建一个接口库目标（如果你想将哈希表作为库使用）
add_library(hashtable INTERFACE)
target_include_directories(hashtable INTERFACE src)
target_compile_features(hashtable INTERFACE cxx_std_20)

# 别名目标，便于在其他项目中使用
add_library(HashTable::hashtable ALIAS hashtable)

# 打印配置信息
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")
