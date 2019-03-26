#include <iostream>
#include <chrono>
#include <set>
#include <functional>
#include <iomanip>
#include <vector>

#include <Treap.h>
#include <SplayTree.h>
#include <utility.h>

#define MEMBER(name)                                                           \
  template <class Tree> void name(Tree &t, std::uint64_t tmp) { t.name(tmp); }

#define ESTIMATE(what)                                                         \
  std::vector<double> what##_ = {estimate(v, t, what<Trees>)...};

#define REPEAT(what) what(insert) what(find) what(erase)

REPEAT(MEMBER)

template <class Tree, class Functor>
double estimate(std::vector<std::uint64_t> &v, Tree &t, Functor f) {
  auto start = std::chrono::system_clock::now();
  for (auto i : v)
    f(t, i);
  auto end = std::chrono::system_clock::now();

  return std::chrono::duration<double>(end - start).count();
}

auto randVec(std::size_t size) {
  std::vector<std::uint64_t> v(size);
  std::generate(v.begin(), v.end(), []() { return utility::get_random(); });
  return v;
}

template <class... Trees>
void initialize(std::vector<std::uint64_t> &v, Trees &... t) {
  ESTIMATE(insert)
}

template <class... Trees>
auto run(std::vector<std::uint64_t> &v, Trees &... t) {
  REPEAT(ESTIMATE)
  return std::vector{insert_, find_, erase_};
}

int main() {
  SplayTree<std::uint64_t> st;
  Treap<std::uint64_t> tp;
  std::set<std::uint64_t> set;

  auto init = randVec(100'000);
  initialize(init, st, tp, set);

  auto v = randVec(10'000);
  auto res = run(v, st, tp, set);

  std::vector ops{"insert", "find ", "erase"};
  std::vector structure{"SplayTree", "Treap ", "std::set"};

  std::cout << std::left << std::setfill(' ') << std::setw(13) << "";
  for (std::size_t i = 0; i < structure.size(); ++i)
    std::cout << std::setw(13) << std::string(i, ' ') + structure[i];
  std::cout << std::endl;

  for (std::size_t i = 0; i < structure.size(); ++i) {
    std::cout << std::setw(13) << ops[i];
    for (auto &time : res[i])
      std::cout << std::setw(13) << time << " ";
    std::cout << std::endl;
  }
}