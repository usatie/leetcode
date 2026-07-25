/*
 講師陣はどのようなコメントを残すだろうか？
  -
 他の人のコードを読んで考えたこと
  - https://github.com/Yoshiki-Iwasa/Arai60/pull/59/files
    1. retainした後にresizeで0埋めするというのはコードとして見通しが良い
    2. &mut nums[1..]という書き方は、コピーにならないのか
       ならないみたい
       https://doc.rust-lang.org/book/ch04-03-slices.html
  - https://github.com/fhiyo/leetcode/pull/54/files
    1. swapするのではなく, あとでまとめて0埋めする方がloop unrollingが効いて
       嬉しいこともあるというのはなるほど目から鱗だった
 改善する時にかんがえたこと
  1. `std::swap(*next_pos++, num)`とか`*next_pos++ =
 num`という書き方もできるけど, error-proneなのでやめた
  2. Iteratorを使わない場合はswapしたいので、numがreferenceとなるよう注意
  3. 0埋めをあとで行うのは,
 filterしたい値が1つだけの場合に有効だが、複数の値をたとえば移動したい場合とかは順番もretainできるしswapがよいかな
 */

#ifndef STEP2_HPP
#define STEP2_HPP

#include <algorithm>
#include <vector>

class Solution {
public:
  // 1. swapを使う
  void moveZeroes1(std::vector<int> &nums) {
    auto next_pos = nums.begin();
    for (auto &num : nums) {
      if (num != 0) {
        std::swap(*next_pos, num);
        ++next_pos;
      }
    }
  }
  // 1-2. swapを使う (with Iterator)
  void moveZeroes12(vector<int> &nums) {
    auto next_pos = nums.begin();
    for (auto it = nums.begin(); it != nums.end(); ++it) {
      if (*it != 0) {
        std::iter_swap(*next_pos, it);
        ++next_pos;
      }
    }
  }
  // 2. swapを使わないで, 0埋めを後で行う
  void moveZeroes2(vector<int> &nums) {
    auto next_pos = nums.begin();
    for (auto &num : nums) {
      if (num != 0) {
        *next_pos = num;
        ++next_pos;
      }
    }
    std::fill(next_pos, nums.end(), 0);
  }
  // 2-2. for/if文をOne-linerっぽく書く (error-proneなので好きではない)
  void moveZeroes22(vector<int> &nums) {
    auto next_pos = nums.begin();
    for (auto num : nums)
      if (num != 0)
        *next_pos++ = num;
    std::fill(next_pos, nums.end(), 0);
  }
};
#endif
