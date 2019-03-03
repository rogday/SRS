#include <cstdint>
#include <iostream>

#include <boost/graph/depth_first_search.hpp>

#include <Graph.h>

int main() {
	std::uint64_t n, m;
	std::cout << "n, m = " << std::endl;
	std::cin >> n >> m;
	auto G = srs::makeGraph(n, m);

	srs::Visitor vis;
	boost::depth_first_search(G, boost::visitor(vis));
}