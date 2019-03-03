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