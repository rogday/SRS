#pragma once

#include <cstdint>
#include <vector>

#include <Graph.h>

namespace srs {
using u64 = std::uint64_t;
constexpr u64 Bytes = 1;
constexpr u64 Bits = Bytes * 8;
constexpr u64 Digits = 8 / Bytes;
constexpr u64 BytesShift = Bytes + 2;
constexpr u64 Variants = u64(1) << Bits;
constexpr u64 Mask = Variants - 1;

void radixSort(std::vector<Graph::Edge> &);
} // namespace srs