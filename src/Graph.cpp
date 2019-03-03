#include <iostream>
#include <Graph.h>
#include <RadixSort.h>


//возможно .index надо менять на .vertex если index - номер ребра
void Graph::dfs(int &v, int &timer, int &backward = -1){
	map[v] = Colors::Grey;
	time_discover[v] = time_minimal[v] = timer++;
	for (auto &e : matrix[v]){
		if (e == backward)
			continue;
		if (map[e.vertex] == Colors::Grey)
			time_minimal[v] = std::min(time_minimal[v], time_discover[e.vertex])
		else{
			dfs(e.vertex, timer, v);
			time_minimal[v] = std::min(time_minimal[v], time_minimal[e.vertex]);
			if (time_minimal[e.vertex] > time_discover[v])
				bridges.push_back(std::pair(v, e.vertex));
		}
	}
	map[v] = Colors::Black;

}

void Graph::determined_bridges_search(){
	int timer = 0;
	for (int i = 0; i < n; ++i){
		if (map[i] != Colors::Black)
			dfs(i, timer);
	}
}

//must be updated
void Graph::dfs_based_randomized_bridges(int &v){
	if (map[v] == Colors::Black)
		return;

	map[v] = Colors::Grey;
	for (auto &e : matrix[v]){
		if (map[e.vertex] != Colors::White){
			e.shift = rand(engine);
			sums[v] ^= e.shift;
			sums[e.vertex] ^= e.shift;
			e.tree_edge = false;
		} else
			e.tree_edge = true;

		dfs_based_randomized_bridges(e.vertex);
		if(e.tree_edge) {
			e.shift = sums[e.vertex];
			sums[v] ^= e.shift;
			sums[e.vertex] = 0;
		}
	}
	map[v] = Colors::Black;
}

std::vector<int> Graph::randomized_bridges(){
	int v = matrix[0].vertex;
	dfs_based_randomized_bridges(v);
	RadixSort::radix_sort(sums);//нельзя сортировать - потеряем индексы. Хм
	//Это все сломает и для 2 мостов
	for (uint64_t i = 0; i < sums.size(); ++i){
		if (sums[i] != 0)
			break;
		//...
	}

}

void Graph::dfsForRandom(std::uint64_t v) {
		if (colorMap[v] != Colors::White)
			return;

		std::cout << "Now in " << v << "===============" << std::endl;

		colorMap[v] = Colors::Grey;
		for (auto &e : matrix[v]) {
			bool tree_edge = false;

			if (colorMap[e.vertex] != Colors::White) {
				if (!e.finished) {
					e.shift = rand(engine);
					sums[v] ^= e.shift;
					sums[e.vertex] ^= e.shift;
					e.finished = true;
				}
			} else {
				tree_edge = true;
				e.finished = true;
				dfsForRandom(e.vertex);
			}

			if (tree_edge) {
				e.shift = sums[e.vertex];
				sums[v] ^= e.shift;
				sums[e.vertex] = 0;
			}
		}
		colorMap[v] = Colors::Black;
	}

void Graph::clear() {
	for (auto &v : matrix)
		for (auto &e : v)
			e.finished = false;
};

Graph::Graph(std::uint64_t n, std::uint64_t m)
		: matrix(n), colorMap(n, Colors::White), sums(n, 0), engine(rd()),
		  rand(0, std::numeric_limits<std::uint64_t>::max()) {
		std::vector<std::uint8_t> helper(n * n);
		std::uniform_int_distribution<std::uint64_t> randomVertex(0, n - 1);
		std::uint64_t u, v;

		auto addEdge = [&]() {
			std::cout << "(" << u << ", " << v << ")" << std::endl;
			helper[u * n + v] = helper[v * n + u] = 1;
			matrix[u].emplace_back(v, false, 0);
			matrix[v].emplace_back(u, false, 0);
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
		dfsForRandom(0);
		for (std::uint64_t i = 0; i < matrix.size(); ++i)
			for (auto &e : matrix[i]) {
				if (e.shift == 0)
					std::cout << "Edge from " << i << " to " << e.vertex
							  << " is a bridge." << std::endl;
			}
	}