#include <chrono>
#include <cmath>
#include <cstdint>
#include <functional>
#include <iostream>

#include <Graph.h>

using namespace std::placeholders;

template <class Functor>
void estimate(Graph &g, std::string_view name, Functor f, bool show) {
    auto start = std::chrono::system_clock::now();
    auto bridges = f(&g);
    auto end = std::chrono::system_clock::now();

    std::cout << name << " search found " << bridges.size()
              << " bridges and worked for "
              << std::chrono::duration<double>(end - start).count() << " sec."
              << std::endl;

    if (show)
        for (auto &e : bridges)
            std::cout << e << std::endl;
}

int main() {
    for (std::uint64_t i = 0; i < 2; ++i) {
        std::cout << ((i) ? "Recursive" : "Iterative") << std::endl;
        for (std::uint64_t n = 10; n < 1'000'000; n *= 10) {
            std::uint64_t m = 2 * n;

            std::cout << n << " " << m << std::endl;

            Graph g(n, m);

            g.random_bridges_search(i); // just to be fair in terms of cache,
                                        // everything is clearing before each
                                        // algorithm

            estimate(g, "Random",
                     std::bind(&Graph::random_bridges_search, _1, i), false);
            estimate(g, "Determenistic",
                     std::bind(&Graph::determined_bridges_search, _1, i),
                     false);
            estimate(g, "Random two-bridges",
                     std::bind(&Graph::random_two_bridges_search, _1, i),
                     false);

            std::cout << std::endl;
        }
    }
}