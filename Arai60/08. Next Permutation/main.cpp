#include "step3.hpp"
#include <iostream>
#include <vector>

#define T(...)                                                                 \
  [&] {                                                                        \
    std::cout << #__VA_ARGS__ " -> ";                                          \
    std::vector<int> nums{__VA_ARGS__};                                        \
    solution.nextPermutation(nums);                                            \
    print_arr(nums);                                                           \
  }()
void print_arr(std::vector<int> &nums) {
  std::cout << "[";
  for (auto it = nums.begin(), end = nums.end(); it != end; ++it) {
    std::cout << *it;
    if (it + 1 != nums.end()) {
      std::cout << ",";
    }
  }
  std::cout << "]" << std::endl;
}

int main() {
  Solution solution;
  T({1, 2, 3});
  T({1, 3, 2});
  T({3, 2, 1});
  T({1, 1, 5});
  T({4, 5, 7, 6, 3, 2, 1});
}
