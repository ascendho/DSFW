#include "../../include/String Equal/StringEqual.hpp"

bool StringEqual(std::string_view str1, std::string_view str2) {
    if (str1.size() != str2.size())
        return false;

    size_t N = str1.size();
    int i = 0;

    while (i < N && str1[i] == str2[i])
        i = i + 1;

    return i == N;
}
