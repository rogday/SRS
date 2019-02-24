#pragma once

#include <array>
#include <numeric>
#include <vector>

namespace srs {
using u64 = std::uint64_t;

inline u64 ind(u64 i, u64 deg) { return (i >> (deg << 4)) & 65535; }

void countSort(std::vector<u64> &A, std::vector<u64> &R, u64 deg) {
	std::array<u64, 65536> B{};

	for (u64 i : A)
		++B[ind(i, deg)];
	std::partial_sum(std::begin(B), std::end(B), std::begin(B));

	for (u64 i = A.size(); i--;)
		R[--B[ind(A[i], deg)]] = A[i];
	std::swap(A, R);
}

void radixSort(std::vector<u64> &A) {
	std::vector<u64> R(A.size());
	for (u64 deg = 0; deg < 4; ++deg)
		countSort(A, R, deg);
}
} // namespace srs