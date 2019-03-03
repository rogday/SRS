#include <array>

#include <RadixSort.h>

using namespace srs;

inline u64 ind(u64 i, u64 deg) { return (i >> (deg << 3)) & 255; }

void srs::radixSort(std::vector<u64> &A) {
	std::vector<u64> R(A.size());
	for (u64 deg = 0; deg < 8; ++deg) {
		std::array<u64, 256> B{};

		for (u64 i : A)
			++B[ind(i, deg)];

		for (u64 i = 1; i < B.size(); ++i)
			B[i] += B[i - 1];

		for (u64 i = A.size(); i--;)
			R[--B[ind(A[i], deg)]] = A[i];
		std::swap(A, R);
	}
}