#include <chrono>
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
  std::uint64_t n, m, recursive;

  std::cout << "Enter n and m: ";
  std::cin >> n >> m;
  std::cout << "Wanna sum recursion? ";
  std::cin >> recursive;

  Graph g(n, m);

  bool show = (n * m <= 1000);
  if (show)
    std::cout << g;

  estimate(g, "Random", std::bind(&Graph::random_bridges_search, _1, recursive),
           show);
  estimate(g, "Random two-bridges",
           std::bind(&Graph::random_two_bridges_search, _1, recursive), show);
  estimate(g, "Determenistic",
           std::bind(&Graph::determined_bridges_search, _1, recursive), show);
}