#include <array>

#include <RadixSort.h>

inline srs::u64 ind(srs::u64 i, srs::u64 deg) {
    return (i >> (deg << srs::BytesShift)) & srs::Mask;
}

void srs::radixSort(std::vector<Graph::Edge> &A) {
    std::vector<Graph::Edge> R(A.size(), A[0]);
    for (u64 deg = 0; deg < Digits; ++deg) {
        std::array<u64, Variants> B{};

        for (auto &i : A)
            ++B[ind(i.shift, deg)];

        for (u64 i = 1; i < B.size(); ++i)
            B[i] += B[i - 1];

        for (u64 i = A.size(); i--;)
            R[--B[ind(A[i].shift, deg)]] = A[i];
        std::swap(A, R);
    }
}