cmake_minimum_required(VERSION 3.28)
project(11___Caches)

set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(include)

# Add executable with main source file
add_executable(11___Caches
        main.cpp
        include/Queue/queue.hpp
        include/Queue/queue.tpp
        include/LRU/LRUCache.hpp
        include/LRU/LRUCache.tpp
)

# Add test executable for cacheLookup function
add_executable(test_cache_lookup
        test_cache_lookup.cpp
        include/Queue/queue.hpp
        include/Queue/queue.tpp
        include/LRU/LRUCache.hpp
        include/LRU/LRUCache.tpp
)

# Add simple test
add_executable(simple_test
        simple_test.cpp
        include/Queue/queue.hpp
        include/Queue/queue.tpp
        include/LRU/LRUCache.hpp
        include/LRU/LRUCache.tpp
)

# Add minimal test (only CacheLookup function, strictly following pseudocode)
add_executable(minimal_test
        minimal_test.cpp
        include/Queue/queue.hpp
        include/Queue/queue.tpp
)
