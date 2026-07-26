/*
  3問連続で正解するのにかかった時間 3:28

  時間計算量: O(N)
  空間計算量: O(1)
*/
#ifndef STEP3_H
#define STEP3_H
#include <algorithm>
#include <iostream>
#include <vector>
class Solution {
public:
  void nextPermutation(std::vector<int> &nums) {
    auto pivot =
        std::adjacent_find(nums.rbegin(), nums.rend(), std::greater<int>());
    if (pivot != nums.rend()) {
      ++pivot;
      auto successor = std::upper_bound(nums.rbegin(), pivot, *pivot);
      std::iter_swap(pivot, successor);
    }
    std::reverse(nums.rbegin(), pivot);
  }
};

/*
 自作してみたデータ構造や関数
*/
namespace playground {
// https://en.cppreference.com/w/cpp/algorithm/adjacent_find
// 初めて使ったため
template <class ForwardIt, class BinaryPred>
ForwardIt adjacent_find(ForwardIt first, ForwardIt last, BinaryPred p) {
  if (first == last)
    return last;
  ForwardIt next = first;
  ++next;
  while (next != last) {
    if (p(*first, *next))
      return first;
    ++next;
    ++first;
  }
  return last;
}

// https://en.cppreference.com/w/cpp/algorithm/upper_bound
// Searches for the first element in the partitioned range [first, last) which
// is ordered AFTER value. いつもlower_boundと使い方を迷うため
template <class ForwardIt,
          class T = typename std::iterator_traits<ForwardIt>::value_type>
ForwardIt upper_bound(ForwardIt first, ForwardIt last, const T &value) {
  return upper_bound(first, last, value, std::less<T>());
}

template <class ForwardIt,
          class T = typename std::iterator_traits<ForwardIt>::value_type,
          class Compare>
ForwardIt upper_bound(ForwardIt first, ForwardIt last, const T &value,
                      Compare comp) {
  auto lo = first, hi = last;
  while (lo < hi) {
    auto mid = lo + (hi - lo) / 2;
    if (!comp(value, *mid)) {
      // *mid <= value
      // i.e. !(*mid > value)
      lo = mid + 1;
    } else {
      hi = mid;
    }
  }
  return lo;
}

// https://en.cppreference.com/w/cpp/algorithm/iter_swap
// 初めて使った
template <class ForwardIt1, class ForwardIt2>
void iter_swap(ForwardIt1 a, ForwardIt2 b) {
  std::swap(*a, *b);
}

// https://en.cppreference.com/w/cpp/algorithm/reverse
template <class BidirIt> void reverse(BidirIt first, BidirIt last) {
  --last;
  while (first < last) {
    std::swap(*first, *last);
    ++first;
    --last;
  }
}

} // namespace playground
#endif
