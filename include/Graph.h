#pragma once

#include <list>
#include <random>
#include <vector>

class Graph {
	friend std::ostream &operator<<(std::ostream &, const Graph &);
	enum Colors { White, Grey, Black }; // for DFS

  public:
	struct LightEdge {
		LightEdge(std::uint64_t u, std::uint64_t v) : u(u), v(v) {}
		std::uint64_t u;
		std::uint64_t v;
		bool operator==(const LightEdge &other) const {
			return (u == other.u && v == other.v);
		}
	};

  private:
	struct Edge : public LightEdge {
		Edge(std::uint64_t u, std::uint64_t v, bool f, std::uint64_t shift)
			: LightEdge(u, v), finished(f), shift(shift) {}
		bool finished;
		std::uint64_t shift;
	};

	// the Graph itself
	std::vector<std::vector<std::uint64_t>> matrix;
	std::vector<Edge> edges;

	// utility
	std::random_device rd;
	std::default_random_engine engine;
	std::uniform_int_distribution<std::uint64_t> rand;

	std::vector<Colors> colorMap;

	// for random algo
	std::vector<std::uint64_t> sums;

	// for determenistic algo
	std::vector<std::uint64_t> time_discover;
	std::vector<std::uint64_t> time_minimal;
	std::vector<LightEdge> bridges;

  private:
	void dfsForRandom(std::uint64_t);
	void dfsForDeterm(std::uint64_t, std::uint64_t &,
					  std::uint64_t backward = -1);

	void clear();

  public:
	Graph(std::uint64_t n, std::uint64_t m);

	using Bridges = std::vector<LightEdge>;
	std::vector<LightEdge> random_bridges_search();
	std::vector<LightEdge> determined_bridges_search();

	std::vector<LightEdge> random_two_bridges_search();
};