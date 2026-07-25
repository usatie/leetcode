#include "step3.hpp"
#include <cassert>
#include <iostream>
#include <vector>

void test(std::initializer_list<int> input,
          std::initializer_list<int> expected) {
  std::vector<int> nums(input);
  std::vector<int> expected_nums(expected);
  std::cout << "input: ";
  for (auto num : nums) {
    std::cout << num << " ";
  }
  Solution().moveZeroes(nums);
  // vectorに== operatorが使えるって知らなかった
  // https://en.cppreference.com/w/cpp/container/vector/operator_cmp
  assert(nums == expected_nums);
  std::cout << " ===== OK =====" << std::endl;
}

int main() {
  test({0, 1, 0, 3, 12}, {1, 3, 12, 0, 0});
  test({0}, {0});
  test({0, 0, 0, 0, 0}, {0, 0, 0, 0, 0});
  test({1, 2, 3, 4, 5}, {1, 2, 3, 4, 5});
}
