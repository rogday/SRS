#include <algorithm>
#include <iostream>
#include <unordered_set>

#include <Graph.h>
#include <RadixSort.h>

namespace std {
template <> struct hash<Graph::LightEdge> {
	std::size_t operator()(const Graph::LightEdge &k) const {
		return std::hash<std::uint64_t>()(k.u) ^
			   std::hash<std::uint64_t>()(k.v);
	}
};
} // namespace std

Graph::Graph(std::uint64_t n, std::uint64_t m)
	: matrix(n), edges(m, Edge(0, 0, false, 0)), colorMap(n, Colors::White),
	  sums(n, 0), engine(rd()),
	  rand(0, std::numeric_limits<std::uint64_t>::max()), time_discover(n),
	  time_minimal(n) {
	std::uniform_int_distribution<std::uint64_t> randomVertex(0, n - 1);
	std::uint64_t u, v, index = 0;

	std::unordered_set<LightEdge> helper;
	helper.reserve(2.2 * m);

	auto addEdge = [&]() {
		helper.emplace(u, v);
		helper.emplace(v, u);
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
			auto it = helper.find(LightEdge{u, v});
			if (it != helper.end())
				u = v;
		} while (u == v);

		addEdge();
	}
};

std::ostream &operator<<(std::ostream &stream, const Graph::LightEdge &e) {
	stream << "(" << e.u << ", " << e.v << ")";
	return stream;
}

std::ostream &operator<<(std::ostream &stream, const Graph::Bridges &bridges) {
	for (auto &e : bridges)
		stream << e << " ";
	return stream;
}

std::ostream &operator<<(std::ostream &stream, const Graph &g) {
	for (auto &e : g.edges)
		stream << e << std::endl;
	return stream;
}

void Graph::clear() {
	bridges.clear();
	for (auto &c : colorMap)
		c = Colors::White;
	for (auto &e : edges)
		e.finished = false;
};

std::vector<Graph::Bridges> Graph::random_two_bridges_search() {
	std::vector<Graph::Bridges> out;
	random_bridges_search();
	srs::radixSort(edges);

	for (auto it = edges.begin(), jt = it; it != edges.end(); jt = it) {
		Graph::Bridges bridges;

		jt = it = std::adjacent_find(jt, edges.end());

		if (jt == edges.end())
			break;

		while (it != edges.end() && *it == *jt) {
			bridges.emplace_back(it->u, it->v);
			++it;
		}

		out.push_back(bridges);
	}

	return out;
};

Graph::Bridges Graph::random_bridges_search() {
	clear();
	dfsForRandom(0);

	for (auto e : edges)
		if (e.shift == 0)
			bridges.emplace_back(e.u, e.v);

	return bridges;
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

Graph::Bridges Graph::determined_bridges_search() {
	clear();
	std::uint64_t timer = 0;
	for (std::uint64_t i = 0; i < colorMap.size(); ++i)
		if (colorMap[i] != Colors::Black)
			Graph::dfsForDeterm(i, timer);
	return bridges;
};

void Graph::dfsForDeterm(std::uint64_t v, std::uint64_t &timer,
						 std::uint64_t backward) {
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
			Graph::dfsForDeterm(vertex, timer, v);
			time_minimal[v] = std::min(time_minimal[v], time_minimal[vertex]);
			if (time_minimal[vertex] > time_discover[v])
				bridges.emplace_back(vertex, v);
		}
	}
	colorMap[v] = Colors::Black;
};
