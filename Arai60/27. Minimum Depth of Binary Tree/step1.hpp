#ifndef STEP1_HPP
#define STEP1_HPP
/**
 * Definition for a binary tree node.
 */
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

#include <queue>

class Solution {
public:
  int minDepth(TreeNode *root) {
    if (root == nullptr)
      return 0;
    std::queue<TreeNode *> visitQueue;
    int depth = 1;
    visitQueue.push(root);
    while (!visitQueue.empty()) {
      int numInThisDepth = visitQueue.size();
      for (int i = 0; i < numInThisDepth; ++i) {
        auto node = visitQueue.front();
        visitQueue.pop();
        if (node->left == nullptr && node->right == nullptr) {
          return depth;
        }
        if (node->left) {
          visitQueue.push(node->left);
        }
        if (node->right) {
          visitQueue.push(node->right);
        }
      }
      ++depth;
    }
    // This should never be reached
    return depth;
  }
};
#endif // STEP1_HPP
