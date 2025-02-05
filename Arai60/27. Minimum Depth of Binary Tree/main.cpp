#include <iostream>
#include <queue>

#include "step3.hpp"

void printTestCase(TreeNode *root) {
  std::cout << "Test case: [";
  std::queue<TreeNode *> nodesToVisit;
  if (root)
    nodesToVisit.push(root);
  while (!nodesToVisit.empty()) {
    auto node = nodesToVisit.front();
    nodesToVisit.pop();
    if (node != root) {
      std::cout << ",";
    }
    if (node == nullptr) {
      std::cout << "null";
    } else {
      std::cout << node->val;
      nodesToVisit.push(node->left);
      nodesToVisit.push(node->right);
    }
  }
  std::cout << "]" << std::endl;
}

void test(TreeNode *root, int expected) {
  printTestCase(root);
  Solution solution;
  int result = solution.minDepth(root);
  if (result == expected) {
    std::cout << "PASSED" << std::endl;
  } else {
    std::cout << "FAILED" << std::endl;
  }
}

int main() {
  test(nullptr, 0);
  test(new TreeNode(1), 1);
  test(new TreeNode(3,
                    new TreeNode(9),
                    new TreeNode(20,
                                 new TreeNode(15),
                                 new TreeNode(7))),
       2);
  test(new TreeNode(2, nullptr,
                    new TreeNode(3, nullptr,
                                 new TreeNode(4, nullptr,
                                              new TreeNode(5, nullptr,
                                                           new TreeNode(6))))),
       5);
}
