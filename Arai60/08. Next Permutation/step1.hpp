/*
  何がわからなかったか
   - 次のpermutationを求めるためのステップの着想を得るのが難しかった

  何を考えて解いていたか
   1. From the tail, find the first asc pair (i, i+1)
   2. find j where nums[j] > nums[i] and j in (i+1, tail)
   3. swap(i, j)
   4. sort(i+1, tail)

  正解してから気づいたこと
   - algorithm系(lower_bound, upper_bound, findなど)を使えば短く綺麗に書けそう
   - いつもalgorithm系はcppreferenceを見て、何度か失敗しながらじゃないと書けない
   - 後ろからiterateするにはrbeginとrendを使えばよさそう
*/
class Solution {
public:
  void nextPermutation(vector<int> &nums) {
    // [1,2,3,4]
    // [1,2,4,3]
    // [1,3,2,4]
    // [1,3,4,2]
    // [1,4,2,3]
    // [1,4,3,2]
    // [2,1,3,4]
    // ...

    // 1. From the tail, find the first asc pair (i, i+1)
    // 2. find j where nums[j] > nums[i] and j in (i+1, tail)
    // 3. swap(i, j)
    // 4. sort(i+1, tail)

    int tail = nums.size() - 1;
    int i, j;
    // 1. Find the first ASC pair nums[i] and nums[i+1]
    bool found = false;
    for (i = tail - 1; i >= 0; --i) {
      if (nums[i] < nums[i + 1]) {
        found = true;
        break;
      }
    }
    if (!found) {
      std::sort(nums.begin(), nums.end());
      return;
    }
    // 2. Find j
    found = false;
    for (j = tail; j >= i + 1; --j) {
      if (nums[j] > nums[i]) {
        found = true;
        break;
      }
    }
    if (!found) {
      std::sort(nums.begin(), nums.end());
      return;
    }
    // 3. swap
    std::swap(nums[i], nums[j]);
    // 4. sort
    std::sort(nums.begin() + i + 1, nums.end());
  }
};
