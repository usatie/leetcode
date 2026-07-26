#include "step3.hpp"
#include <iostream>
#include <queue>

#define null 9999999

TreeNode *buildTree(std::initializer_list<int> values) {
  if (values.size() == 0) {
    return nullptr;
  }
  TreeNode *root = new TreeNode(*values.begin());
  std::queue<TreeNode *> nodes;
  nodes.push(root);
  for (size_t i = 1; i < values.size(); ++i) {
    auto node = nodes.front();
    nodes.pop();
    int val1 = *(values.begin() + i);
    int val2 = *(values.begin() + ++i);
    if (val1 != null) {
      node->left = new TreeNode(val1);
      nodes.push(node->left);
    }
    if (val2 != null) {
      node->right = new TreeNode(val2);
      nodes.push(node->right);
    }
  }
  return root;
}

void printTestCase(std::initializer_list<int> values) {
  std::cout << "Test case: [";
  for (auto it = values.begin(); it != values.end(); ++it) {
    if (*it == null) {
      std::cout << "null";
    } else {
      std::cout << *it;
    }
    if (it != values.end() - 1) {
      std::cout << ",";
    }
  }
  std::cout << "]" << std::endl;
}

void test(std::initializer_list<int> values, int expected) {
  TreeNode *root = buildTree(values);
  printTestCase(values);
  Solution solution;
  int result = solution.minDepth(root);
  if (result == expected) {
    std::cout << "PASSED" << std::endl;
  } else {
    std::cout << "FAILED" << std::endl;
  }
}

int main() {
  test({}, 0);
  test({1}, 1);
  test({3, 9, 20, null, null, 15, 7}, 2);
  test({2, null, 3, null, 4, null, 5, null, 6}, 5);
}
