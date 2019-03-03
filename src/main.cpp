#include <chrono>
#include <cstdint>
#include <iostream>

#include <Graph.h>

int main() {
	std::uint64_t n, m;
	std::cout << "n, m = " << std::endl;
	std::cin >> n >> m;

	srs::Graph G(n, m);

	auto start = std::chrono::system_clock::now();
	G.randomBridgeSearch();
	auto end = std::chrono::system_clock::now();

	std::cout << "Time: " << std::chrono::duration<double>(end - start).count()
			  << " sec." << std::endl;
}