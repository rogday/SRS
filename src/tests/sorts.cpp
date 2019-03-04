#include <cassert>
#include <chrono>
#include <cstdint>
#include <functional>
#include <iostream>

#include <Graph.h>
#include <RadixSort.h>

int main() {
	std::random_device r;
	std::default_random_engine e1(r());
	std::uniform_int_distribution<srs::u64> uniform_dist(
		0, std::numeric_limits<srs::u64>::max());

	for (std::uint64_t i = 1; i <= 10'000; i *= 10) {
		std::vector<Graph::Edge> v1(10'000 * i, Graph::Edge(0, 0, false, 0));

		std::cout << v1.size() << std::endl;
		for (auto &i : v1)
			i.shift = uniform_dist(e1);
		std::vector v2(v1);

		auto start = std::chrono::system_clock::now();
		srs::radixSort(v1);
		auto end = std::chrono::system_clock::now();

		std::cout << "Radix sort: "
				  << std::chrono::duration<double>(end - start).count()
				  << " sec." << std::endl;

		start = std::chrono::system_clock::now();
		std::sort(std::begin(v2), std::end(v2),
				  [](const Graph::Edge &e1, const Graph::Edge &e2) {
					  return e1.shift < e2.shift;
				  });
		end = std::chrono::system_clock::now();

		std::cout << "std::sort: "
				  << std::chrono::duration<double>(end - start).count()
				  << " sec." << std::endl
				  << std::endl;

		assert(v1 == v2);
	}
}