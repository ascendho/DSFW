#pragma once

#include <concepts>

template<typename T>
requires std::totally_ordered<T>
void InsertionSort(std::vector<T> &A) {
    size_t N = A.size();
    int i = 1;

    while (i < N) {
        auto current = std::move(A[i]);
        int j = i - 1;

        while (j >= 0 && A[j] > current) {
            A[j + 1] = std::move(A[j]);
            j = j - 1;
        }
        A[j + 1] = std::move(current);
        i = i + 1;
    }
}
