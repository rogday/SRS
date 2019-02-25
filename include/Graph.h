#pragma once

#include <cstdint>
#include <vector>

class Graph {
	using u64 = std::uint64_t;
	using u8 = std::uint8_t;

  private:
	u64 _m; // edges
	u64 _n; // vertices
	std::vector<u8> _mat;
	std::vector<u8> _span;
	std::vector<u8> _vsum;

  public:
	Graph(u64 n, u64 m) : _m(m), _n(n), _mat(_m * _n), _span(_m), _vsum(_n) {}

	u8 &at(u64 i, u64 j) { return _mat[i * _m + j]; }

	void add_edge(u64 u, u64 v) {
		static u64 i = 0;
		at(u, i) = at(v, i) = 1;
		++i;
	}

	void get_span() {
		for (u64 i = 0; i < _n; ++i) {
		}
	}
};