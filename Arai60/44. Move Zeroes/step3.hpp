#ifndef STEP3_HPP
#define STEP3_HPP

#include <algorithm>
#include <vector>
using std::iter_swap;
using std::vector;

/*
  3問連続で正解するのにかかった時間 2:57
  時間計算量: O(N)
  空間計算量: O(1)
*/
class Solution {
public:
  void moveZeroes(std::vector<int> &nums) {
    auto next = nums.begin();
    for (auto it = nums.begin(); it != nums.end(); ++it) {
      if (*it != 0) {
        std::iter_swap(it, next);
        ++next;
      }
    }
  }
};
#endif
