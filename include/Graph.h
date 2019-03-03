#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <random> 


class Graph{
	enum Colors { White, Gray, Black };
	struct Node{
		int vertex;
		int index;
		bool tree_edge;
		std::uint64_t shift;
	};
	std::vector<std::list<Node>> matrix;
	std::vector<Colors> map;
	std::vector<std::uint64_t> sums;

	std::vector<int> det_bridges;
	std::vector<int> rand_bridges;

	std::vector<int> time_discover(matrix.size(), 0);
	std::vector<int> time_minimal(matrix.size(), 0);//min(time_disc[v], time_disc[backward_edges])

	std::random_device rd;
	std::default_random_engine engine;
	std::uniform_int_destribution<std::uint64_t> rand;

public:
	Graph() : engine(rd()) {}
	void dfs(int&, int&);
	//bridges search methods
	void determined_bridges_search();

	void dfs_based_randomized_bridges_search();
	std::vector<int> randomized_bridges_search(int&);

	//2-bridges search method


}