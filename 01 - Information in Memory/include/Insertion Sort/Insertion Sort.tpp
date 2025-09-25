#pragma once

template<typename T>
void InsertionSort(std::vector<T> &A) {
    size_t N = A.size();
    size_t i = 1;

    while (i < N) {
        auto current = A[i];
        size_t j = i - 1;

        while (j < N && A[j] > current) {
            A[j + 1] = A[j];
            j = j - 1;
        }
        A[j + 1] = current;
        i = i + 1;
    }
}
