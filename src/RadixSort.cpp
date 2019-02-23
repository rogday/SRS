#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <iostream>
#include <limits>
#include <numeric>
#include <random>
#include <vector>

namespace test {
using u64 = std::uint64_t;
constexpr u64 Bytes = 2;
constexpr u64 Bits = 8 * Bytes;
constexpr u64 C = (static_cast<u64>(1) << Bits);

u64 ind(u64 i, u64 deg) { return (i >> (deg << 4)) % C; }

void countSort(std::vector<u64> &A, std::vector<u64> &R, u64 deg) {
	std::array<u64, C> B{};

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
} // namespace test

int main() {
	std::random_device r;
	std::default_random_engine e1(r());
	std::uniform_int_distribution<test::u64> uniform_dist(
		0, std::numeric_limits<test::u64>::max());

	std::vector<test::u64> v1(100'000);
	for (test::u64 &i : v1)
		i = uniform_dist(e1);
	std::vector v2(v1);

	auto start = std::chrono::system_clock::now();
	test::radixSort(v1);
	auto end = std::chrono::system_clock::now();

	std::cout << "Radix sort: "
			  << std::chrono::duration<double>(end - start).count() << " sec."
			  << std::endl;

	start = std::chrono::system_clock::now();
	std::sort(std::begin(v2), std::end(v2));
	end = std::chrono::system_clock::now();

	std::cout << "std::sort: "
			  << std::chrono::duration<double>(end - start).count() << " sec."
			  << std::endl;

	assert(v1 == v2);
}
