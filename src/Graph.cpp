#include <Graph.h>
#include <RadixSort.h>
#include <iostream>

void Graph::dfs(int v, int &timer, uint64_t backward = -1) {
	if (colorMap[v] != Colors::White)
		return;

	colorMap[v] = Colors::Grey;
	time_discover[v] = time_minimal[v] = timer++;
	for (auto index : matrix[v]) {
		auto &e = edges[index];
		std::uint64_t vertex = (e.v == v) ? e.u : e.v;

		if (vertex == backward)
			continue;
		if (colorMap[vertex] == Colors::Grey) {
			time_minimal[v] = std::min(time_minimal[v], time_discover[vertex]);
		} else {
			Graph::dfs(vertex, timer, v);
			time_minimal[v] = std::min(time_minimal[v], time_minimal[vertex]);
			if (time_minimal[vertex] > time_discover[v])
				bridges.push_back(Edge(vertex, v, true, 0));
		}
	}
	colorMap[v] = Colors::Black;
};

void Graph::determined_bridges_search() {
	clear();
	int timer = 0;
	for (int i = 0; i < colorMap.size(); ++i) {
		if (colorMap[i] != Colors::Black)
			Graph::dfs(i, timer);
	}
};

void Graph::dfsForRandom(std::uint64_t v) {
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
};

void Graph::clear() {
	for (auto &c : colorMap)
		c = Colors::White;
	for (auto &e : edges)
		e.finished = false;
};

Graph::Graph(std::uint64_t n, std::uint64_t m)
	: matrix(n), edges(m, Edge(0, 0, false, 0)), colorMap(n, Colors::White),
	  sums(n, 0), engine(rd()),
	  rand(0, std::numeric_limits<std::uint64_t>::max()), time_discover(n),
	  time_minimal(n) {
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
};

void Graph::randomBridgeSearch() {
	clear();
	dfsForRandom(0);
	// bool flag = true;
	int i = 0;

	for (auto e : edges)
		if (e.shift == 0) {
			++i;
			// std::cout << "Edge from " << e.u << " to " << e.v << " is a
			// bridge."
			//		  << std::endl;
			// flag = false;
		}
	// if (flag)
	//	std::cout << "There are no bridges!" << std::endl;
	std::cout << i << std::endl;
};