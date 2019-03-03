#pragma once

#include <iostream>
#include <list>
#include <random>
#include <vector>

namespace srs {

class Graph {
	enum Colors { White, Grey, Black };
	struct Edge {
		Edge(std::uint64_t u, std::uint64_t v, bool f, std::uint64_t shift)
			: u(u), v(v), finished(f), shift(shift) {}
		std::uint64_t u;
		std::uint64_t v;
		bool finished;
		std::uint64_t shift;
	};
	std::vector<std::vector<std::uint64_t>> matrix;
	std::vector<Edge> edges;

	std::vector<Colors> colorMap;
	std::vector<std::uint64_t> sums;

	std::random_device rd;
	std::default_random_engine engine;
	std::uniform_int_distribution<std::uint64_t> rand;

  private:
	void dfsForRandom(std::uint64_t v) {
		if (colorMap[v] != Colors::White)
			return;

		colorMap[v] = Colors::Grey;
		for (auto index : matrix[v]) {
			auto &e = edges[index];
			std::uint64_t u = ((e.u == v) ? e.v : e.u);
			bool tree_edge = false;

			if (colorMap[u] != Colors::White) {
				if (!e.finished) {
					e.shift = rand(engine);
					sums[v] ^= e.shift;
					sums[u] ^= e.shift;
					e.finished = true;
				}
			} else {
				tree_edge = true;
				e.finished = true;
				dfsForRandom(u);
			}

			if (tree_edge) {
				e.shift = sums[u];
				sums[v] ^= e.shift;
				sums[u] = 0;
			}
		}
		colorMap[v] = Colors::Black;
	}

	void clear() {
		for (auto &e : edges)
			e.finished = false;
	};

  public:
	Graph(std::uint64_t n, std::uint64_t m)
		: matrix(n), edges(m, Edge(0, 0, false, 0)), colorMap(n, Colors::White),
		  sums(n, 0), engine(rd()),
		  rand(0, std::numeric_limits<std::uint64_t>::max()) {
		std::vector<std::uint8_t> helper(n * n);
		std::uniform_int_distribution<std::uint64_t> randomVertex(0, n - 1);
		std::uint64_t u, v, index = 0;

		auto addEdge = [&]() {
			std::cout << "(" << u << ", " << v << ")" << std::endl;
			helper[u * n + v] = helper[v * n + u] = 1;
			matrix[u].push_back(index);
			matrix[v].push_back(index);
			edges[index].v = v;
			edges[index++].u = u;
		};

		for (v = 1; v <= n - 1; ++v) {
			std::uniform_int_distribution<std::uint64_t> vertex(0, v - 1);
			u = vertex(engine);
			addEdge();
		}

		for (std::uint64_t i = 0; i < m - n + 1; ++i) {
			do {
				u = randomVertex(engine);
				v = randomVertex(engine);
			} while (helper[u * n + v] != 0 || u == v);

			addEdge();
		}
	}

	void randomBridgeSearch() {
		dfsForRandom(0);
		int i = 0;
		for (auto e : edges)
			if (e.shift == 0)
				++i;
		// std::cout << "Edge from " << e.u << " to " << e.v
		//		  << " is a bridge." << std::endl;
		std::cout << i << std::endl;
	}
};

} // namespace srs