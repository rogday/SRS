#pragma once

#include <random>

#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/random.hpp>

namespace srs {
struct tree_edge {
	typedef boost::edge_property_tag kind;
};
struct shift {
	typedef boost::edge_property_tag kind;
};

typedef boost::property<tree_edge, bool, boost::property<shift, std::uint64_t>>
	EdgeProperty;

typedef boost::property<boost::vertex_degree_t, std::uint64_t> VertexProperty;

typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS,
							  EdgeProperty, VertexProperty>
	Graph;

Graph makeGraph(std::uint64_t n, std::uint64_t m);

class Visitor : public boost::default_dfs_visitor {
  public:
	typedef Graph::edge_descriptor Edge;
	void examine_edge(Edge v, const Graph &g);
	void tree_edge(Edge v, const Graph &g);
	void finish_edge(Edge v, const Graph &g);
};
} // namespace srs