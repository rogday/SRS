#include <iostream>

#include <Graph.h>

srs::Graph srs::makeGraph(std::uint64_t n, std::uint64_t m) {
	std::random_device r;
	std::default_random_engine e1(r());

	srs::Graph g;
	boost::generate_random_graph(g, n, m, e1, false, false);

	std::ofstream f("graph.dot");
	boost::write_graphviz(f, g);
	f.close();
	system("dot graph.dot -Kcirco -Tsvg -o graph.svg");
	system("display -size 800x600 graph.svg&");
	return g;
}

void srs::Visitor::examine_edge(srs::Visitor::Edge v, const srs::Graph &g) {
	std::cout << "examine_edge " << v << std::endl;
};
void srs::Visitor::tree_edge(srs::Visitor::Edge v, const srs::Graph &g) {
	std::cout << "tree_edge " << v << std::endl;
};
void srs::Visitor::finish_edge(srs::Visitor::Edge v, const srs::Graph &g) {
	std::cout << "finish_edge " << v << std::endl;
};