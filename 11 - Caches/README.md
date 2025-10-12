# LRU Cache Implementation

基于《Data Structures the Fun Way》第11章的LRU(Least Recently Used)缓存实现。

## 数据结构概述

### 1. 队列 (Queue)
使用双向链表实现的队列，支持以下操作：
- **Enqueue**: 在队列尾部添加元素
- **Dequeue**: 从队列头部移除元素
- **RemoveNode**: 从队列中间移除特定节点

队列用于跟踪缓存条目的访问顺序：
- 队列头部 = 最久未使用的元素
- 队列尾部 = 最近使用的元素

### 2. 缓存条目 (CacheEntry)
每个缓存条目包含：
- `key`: 键值
- `value`: 存储的数据
- `node`: 指向队列中对应节点的指针

### 3. LRU缓存 (LRUCache)
组合哈希表和队列实现的LRU缓存：
- **哈希表 (unordered_map)**: 提供 O(1) 的快速查找
- **队列 (Queue)**: 跟踪访问顺序，支持 O(1) 的驱逐操作

## 核心功能

### cacheLookup(key, dataRetriever)
**书中描述的核心函数**，结合缓存查找和数据检索：
1. 在缓存中查找键
2. 如果找到（缓存命中）：
   - 更新访问顺序
   - 返回缓存的值
   - **不调用** dataRetriever
3. 如果未找到（缓存未命中）：
   - 调用 dataRetriever 从慢速数据源获取数据
   - 如果缓存已满，驱逐最久未使用的条目
   - 将新数据插入缓存
   - 返回获取的值

**详细文档**: 参见 [CACHE_LOOKUP.md](CACHE_LOOKUP.md)

### get(key)
获取键对应的值：
1. 在哈希表中查找键
2. 如果找到（缓存命中）：
   - 将该元素从队列当前位置移除
   - 重新添加到队列尾部（标记为最近使用）
   - 返回值
3. 如果未找到（缓存未命中）：
   - 返回 std::nullopt

### put(key, value)
插入或更新键值对：
1. 如果键已存在：
   - 更新值
   - 更新访问顺序（移到队列尾部）
2. 如果键不存在：
   - 检查缓存是否已满
   - 如果已满，驱逐最久未使用的元素（队列头部）
   - 插入新元素到哈希表
   - 将键添加到队列尾部

### remove(key)
从缓存中移除指定键：
1. 在哈希表中查找
2. 从队列中移除对应节点
3. 从哈希表中删除条目

### clear()
清空所有缓存条目

## 时间复杂度

| 操作 | 时间复杂度 |
|------|-----------|
| get  | O(1)      |
| put  | O(1)      |
| remove | O(1)    |
| clear | O(n)     |

## 空间复杂度

O(capacity) - 存储最多 capacity 个缓存条目

## LRU驱逐策略

当缓存满时，LRU策略会驱逐**最久未使用**的元素：
- 队列维护访问顺序
- 每次访问将元素移到队列尾部
- 驱逐时移除队列头部的元素

### 适用场景

✅ **适合的场景**：
- Web浏览器缓存（页面元素重复访问）
- 数据库查询结果缓存
- 最近访问的文件列表
- 咖啡店订单缓存（顾客倾向于订购类似的饮品）

❌ **不适合的场景**：
- 访问模式完全随机
- 新数据比旧数据更不可能被访问（应使用MRU）
- 某些数据访问频率远高于其他数据（应使用LFU）

## 示例用法

### 基本操作 (get/put)

```cpp
#include "include/LRU/LRUCache.hpp"

// 创建容量为3的缓存
LRUCache<int, std::string> cache(3);

// 添加数据
cache.put(1, "Coffee");
cache.put(2, "Tea");
cache.put(3, "Latte");

// 获取数据
auto value = cache.get(1);  // 返回 "Coffee"

// 添加第4个元素会驱逐最久未使用的元素（键2）
cache.put(4, "Espresso");

// 键2已被驱逐
auto missing = cache.get(2);  // 返回 std::nullopt
```

### cacheLookup 函数（推荐）

```cpp
// 创建缓存
LRUCache<int, std::string> cache(3);

// 定义数据检索函数（模拟慢速数据源）
auto dataRetriever = [](const int& key) -> std::string {
    // 这里可以是数据库查询、网络请求、文件读取等
    return fetchDataFromSlowSource(key);
};

// 使用 cacheLookup - 自动处理缓存命中和未命中
std::string data1 = cache.cacheLookup(1, dataRetriever);
// 第一次：调用 dataRetriever 获取数据并缓存

std::string data2 = cache.cacheLookup(1, dataRetriever);
// 第二次：直接从缓存返回，不调用 dataRetriever（快！）
```

**更多示例**: 参见 [CACHE_LOOKUP.md](CACHE_LOOKUP.md)

## 咖啡店类比

就像书中描述的咖啡店场景：
- **收银台旁的加热器** = LRU缓存
- **远端的咖啡站** = 慢速数据存储
- **最近点的咖啡** = 缓存中的数据
- **很久没点的咖啡** = 被驱逐的数据

当顾客点咖啡时：
- 如果正好是收银台旁的咖啡（缓存命中）→ 立即服务 ✨
- 如果不是（缓存未命中）→ 需要走到远端咖啡站

## 编译和运行

```bash
# 配置CMake
cmake -B build -S .

# 编译
cmake --build build

# 运行基本测试（get/put操作）
./build/11___Caches

# 运行 cacheLookup 函数测试
./build/test_cache_lookup

# 运行简单测试（验证缓存命中）
./build/simple_test
```

## 测试程序

| 程序 | 说明 |
|------|------|
| `11___Caches` | 测试基本的 get/put/remove/clear 操作 |
| `test_cache_lookup` | 演示 cacheLookup 函数的实际应用场景 |
| `simple_test` | 简单测试，验证缓存命中率 ✅ |

## 其他驱逐策略对比

### MRU (Most Recently Used)
- 驱逐**最近使用**的元素
- 适合：电子书阅读器（不太可能连续读两遍同一本书）

### LFU (Least Frequently Used)
- 驱逐**使用次数最少**的元素
- 适合：家庭咖啡收藏（保留常喝的品种）
- 缺点：新的热门项需要时间才能进入缓存

### 预测驱逐 (Predictive Eviction)
- 基于模型预测未来访问模式
- 优点：准确模型可大幅提升命中率
- 缺点：复杂度高，需要维护预测模型

## 参考资料

- 《Data Structures the Fun Way》第11章 - Caches
- LRU缓存是常见面试题（LeetCode #146）
