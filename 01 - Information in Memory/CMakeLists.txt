cmake_minimum_required(VERSION 4.0)
project(01___Information_in_Memory LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 设置编译选项
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
        add_compile_options(-Wall -Wextra -pedantic)
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")
endif ()

# Collect sources and headers (handle spaces in directories)
file(GLOB_RECURSE PROJECT_HEADERS RELATIVE ${CMAKE_SOURCE_DIR}
        "include/*.hpp" "include/*.tpp" "include/*.h"
)
file(GLOB_RECURSE PROJECT_SOURCES RELATIVE ${CMAKE_SOURCE_DIR}
        "src/*.cpp" "src/*.cc" "src/*.cxx"
)

# If there are any .cpp sources in src/, build them into a library so tests and demo can link to them
if(PROJECT_SOURCES)
        add_library(dstfw_core STATIC ${PROJECT_SOURCES})
        target_include_directories(dstfw_core PUBLIC ${CMAKE_SOURCE_DIR}/include)
        target_compile_features(dstfw_core PUBLIC cxx_std_20)
endif()

# Optionally build a demo executable. Default OFF to prefer tests-first workflow.
option(BUILD_DEMO "Build demo executable (requires main.cpp)" OFF)
if(BUILD_DEMO)
        # Ensure main exists and add it explicitly
        set(MAIN_SRC ${CMAKE_SOURCE_DIR}/main.cpp)
        if(NOT EXISTS ${MAIN_SRC})
                message(FATAL_ERROR "main.cpp not found at ${MAIN_SRC}")
        endif()

        add_executable(01___Information_in_Memory
                ${MAIN_SRC}
                ${PROJECT_SOURCES}
                ${PROJECT_HEADERS} # allows IDEs to see headers
        )

        # (If BUILD_DEMO is ON, demo target settings are set inside that branch)
endif()

# (demo target settings are applied inside the BUILD_DEMO branch)

# 打印配置信息
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")

# 可选：添加简单的测试（默认开启）
option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
        enable_testing()
        find_package(GTest REQUIRED)

        # 全局包含目录（和 10 - Hash Tables 的写法一致）
        include_directories(${CMAKE_SOURCE_DIR}/include)

        # Test: insertion sort
        add_executable(test_insertion_sort
                test/test_insertion_sort.cpp
        )
        if(TARGET dstfw_core)
                target_link_libraries(test_insertion_sort PRIVATE dstfw_core GTest::gtest_main)
        else()
                target_link_libraries(test_insertion_sort PRIVATE GTest::gtest_main)
        endif()
        set_target_properties(test_insertion_sort PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
        add_test(NAME insertion_sort_test COMMAND test_insertion_sort)

        # Test: string equal
        add_executable(test_string_equal
                test/test_string_equal.cpp
        )
        if(TARGET dstfw_core)
                target_link_libraries(test_string_equal PRIVATE dstfw_core GTest::gtest_main)
        else()
                target_link_libraries(test_string_equal PRIVATE GTest::gtest_main)
        endif()
        set_target_properties(test_string_equal PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
        add_test(NAME string_equal_test COMMAND test_string_equal)

        message(STATUS "Building with tests enabled")
endif()
