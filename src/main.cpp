#include <cstdint>
#include <iostream>

#include <boost/graph/depth_first_search.hpp>

#include <Graph.h>

int main() {
	std::uint64_t n, m;
	std::cout << "n, m = " << std::flush;
	std::cin >> n >> m;

	Graph* g = new Graph(n,m);
	
	g -> Graph::randomBridgeSearch();

	g -> Graph::determined_bridges_search();

	std::cout<<"FU"<<std::endl;

	bool flag = true;
		
	for (auto& i : g -> bridges){
		std::cout << i.u <<"-"<< i.v << "; "<<std::flush;
		flag = false;
	}
	if (flag)
			std::cout<<"There are no bridges!" <<std::endl;

	
}