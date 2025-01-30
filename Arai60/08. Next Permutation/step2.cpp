class Solution {
public:
  void nextPermutation(std::vector<int> &nums) {
    // Find the first DSC pair from the tail : [4,(5,7),6,3,2,1]
    auto pivot =
        std::adjacent_find(nums.rbegin(), nums.rend(), std::greater<int>());
    if (pivot != nums.rend()) {
      ++pivot; // to point to the second element of the pair :
               // [4,(*5,7),6,3,2,1]
      // to find the successor of pivot : [4,(*5,7),**6,3,2,1]
      auto successor = std::upper_bound(nums.rbegin(), pivot, *pivot);
      std::iter_swap(pivot, successor);
    }
    std::reverse(nums.rbegin(), pivot);
  }
};
