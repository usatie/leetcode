/*
  3問連続で正解するのにかかった時間 10分
  時間計算量: O(N)
  空間計算量: O(N)
*/

#ifndef STEP3_HPP
#define STEP3_HPP

#include <queue>

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right): val(x), left(left), right(right) {}
};

class Solution {
public:
  int minDepth(TreeNode *root) {
    if (root == nullptr) return 0;
    std::queue<std::tuple<TreeNode*, int>> visitQueue;
    visitQueue.emplace(root, 1);
    while (!visitQueue.empty()) {
      auto [node, depth] = visitQueue.front();
      visitQueue.pop();
      if (node->left == nullptr && node->right == nullptr) return depth;
      if (node->left) visitQueue.emplace(node->left, depth + 1);
      if (node->right) visitQueue.emplace(node->right, depth + 1);
    }
    __builtin_unreachable();
  }
};
#endif
