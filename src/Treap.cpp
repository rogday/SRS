#include <Treap.h>

std::random_device Treap::Node::rd;
std::default_random_engine Treap::Node::engine(rd());
std::uniform_int_distribution<std::uint64_t>
	Treap::Node::rand(0, std::numeric_limits<std::uint64_t>::max());