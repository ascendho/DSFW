#include "Hash Functions/StringHash.hpp"

size_t StringHash(const std::string &key, size_t size) noexcept {
    size_t total = 0;
    for (const auto &character: key) {
        // 警告⚠️：长字符串可能会导致 size_t 溢出
        total = CONST * total + characterToNumber(character);
    }

    return total % size;
}
