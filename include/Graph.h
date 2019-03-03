#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <random> 


class Graph{
enum Colors { White, Grey, Black };
	struct Edge {
		Edge(std::uint64_t v, bool f, std::uint64_t shift)
			: vertex(v), finished(f), shift(shift) {}
		std::uint64_t vertex;
		bool finished;
		std::uint64_t shift;
	};
	std::vector<std::vector<Edge>> matrix; //здесь вектор, но пробелов быть не должно.
	std::vector<Colors> colorMap;
	std::vector<std::uint64_t> sums;

	std::random_device rd;
	std::default_random_engine engine;
	std::uniform_int_distribution<std::uint64_t> rand;

	std::vector<int> time_discover(matrix.size(), 0);
	std::vector<int> time_minimal(matrix.size(), 0);//min(time_disc[v], time_disc[backward_edges])

private:
	void dfsForRandom(std::uint64_t v);
	void clear();
public:
	Graph(std::uint64_t n, std::uint64_t m);
	void randomBridgeSearch();



	void dfs(int&, int&);
	//bridges search methods
	void determined_bridges_search();

	void dfs_based_randomized_bridges_search();
	std::vector<int> randomized_bridges_search(int&);

	//2-bridges search method
};