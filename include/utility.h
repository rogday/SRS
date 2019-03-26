#pragma once

#include <random>

namespace utility {
template <class T = std::uint64_t>
auto get_random(T min = 0, T max = std::numeric_limits<std::uint64_t>::max()) {
  static std::random_device rd;
  static std::default_random_engine engine(rd());
  static std::uniform_int_distribution<std::uint64_t> rand(min, max);
  return rand(engine);
}
}; // namespace utility