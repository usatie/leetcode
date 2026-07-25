/*
  何がわからなかったか
   - N/A
  何を考えて解いていたか
   1. In place -> swapを使いたい
   2. Use two pointers, one for next insert position, the other for cursor
   3. When it == next_it, swap is not necessary but it's okay
  正解してから気づいたこと
   - N/A
*/
#ifndef STEP1_HPP
#define STEP1_HPP
#include <algorithm>
#include <vector>
class Solution {
public:
  void moveZeroes(std::vector<int> &nums) {
    auto next_it = nums.begin();
    for (auto it = nums.begin(); it < nums.end(); ++it) {
      if (*it != 0) {
        std::iter_swap(next_it, it);
        ++next_it;
      }
    }
  }
};
#endif
