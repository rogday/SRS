#include <chrono>
#include <cstdint>
#include <functional>
#include <iostream>

#include <Graph.h>

using namespace std::placeholders;

template <class Functor>
void estimate(Graph &g, std::string_view name, Functor f) {
	auto start = std::chrono::system_clock::now();
	auto bridges = f(&g);
	auto end = std::chrono::system_clock::now();

	std::cout << name << " search found " << bridges.size()
			  << " bridges and worked for "
			  << std::chrono::duration<double>(end - start).count() << " sec."
			  << std::endl;

	// for (auto &e : bridges) {
	//	for (auto &ee : e) {
	//		std::cout << "(" << ee.u << ", " << ee.v << ") ";
	//	}
	//	std::cout << std::endl;
	//}
}

int main() {
	std::uint64_t n, m;
	std::cin >> n >> m;

	Graph g(n, m);
	std::cout << g;

	// estimate(g, "Random", std::bind(&Graph::random_bridges_search, _1));
	// estimate(g, "Determenistic",
	//		 std::bind(&Graph::determined_bridges_search, _1));
	estimate(g, "Random two-bridges",
			 std::bind(&Graph::random_two_bridges_search, _1));
}