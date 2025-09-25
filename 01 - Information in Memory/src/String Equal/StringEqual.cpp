#include "../../include/String Equal/StringEqual.hpp"

bool StringEqual(const std::string &str1, const std::string &str2) {
    if (str1.size() != str2.size())
        return false;

    size_t N = str1.size();
    size_t i = 0;

    while (i < N && str1[i] == str2[i])
        i = i + 1;

    return i == N;
}
