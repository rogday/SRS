#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>
#include <limits>
#include <random>
#include <vector>

#include <RadixSort.h>

int main() {
	std::random_device r;
	std::default_random_engine e1(r());
	std::uniform_int_distribution<srs::u64> uniform_dist(
		0, std::numeric_limits<srs::u64>::max());

	std::vector<srs::u64> v1(100'000);
	for (srs::u64 &i : v1)
		i = uniform_dist(e1);
	std::vector v2(v1);

	auto start = std::chrono::system_clock::now();
	srs::radixSort(v1);
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
