#pragma once

#include <cstdint>
#include <vector>

#include <Graph.h>

namespace srs {
using u64 = std::uint64_t;

void radixSort(std::vector<Graph::Edge> &);
} // namespace srs