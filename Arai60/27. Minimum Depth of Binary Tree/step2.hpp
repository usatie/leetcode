/*
 講師陣はどのようなコメントを残すだろうか？
  - コードの移植性について
 他の人のコードを読んで考えたこと
  - https://github.com/colorbox/leetcode/pull/36
    pushの代わりにemplaceを使っているが、どう違うんだっけ
  - (!ptr)と(ptr == nullptr)は
    郷に行っては郷に従えスタンスだけど、自分で書く場合はいつも迷う。
    個人的には前者は短いけど分かりづらく、後者好きだけど長くなる。

 改善する時にかんがえたこと
  - そもそもgcc/clang以外でコンパイルしたことがないから他のコンパイラ(主にMSVC?)のためにどれくらいポータブルなコードを書くべきなのかがよくわかっていない。
    (std::unreachableはC++23からで新しすぎるかな）
    https://en.cppreference.com/w/cpp/utility/unreachable
  - なるほど、新しく値をコンストラクトしてpushするとcopy/moveしてしまうので、
    コンストラクタの引数をemplaceに渡す方が効率が良いということか。
    https://en.cppreference.com/w/cpp/container/queue/emplace
    https://stackoverflow.com/questions/26198350/c-stacks-push-vs-emplace
  - DFSで書くときには、当初leftかrightが0の場合を考慮せずreturnしてしまった
    なんか考慮漏れがあってスッと書けない感じがした

*/
#ifndef STEP2_HPP
#define STEP2_HPP
/**
 * Definition for a binary tree node.
 */
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

#include <queue>
#include <utility>

class Solution {
public:
  // 1. depthをqueueに
  // 2. __builtin_unreachable()を使ってみた（gcc/clangのみだが）
  // 3. pushの代わりにemplaceを使ってみた
  int minDepth(TreeNode* root) {
    if (root == nullptr) return 0;
    std::queue<std::tuple<TreeNode *, int>> visitQueue;
    visitQueue.emplace(root, 1);
    while (!visitQueue.empty()) {
      auto [node, depth] = visitQueue.front();
      visitQueue.pop();
      if (node->left == nullptr && node->right == nullptr) { return depth; }
      if (node->left) { visitQueue.emplace(node->left, depth + 1); }
      if (node->right) { visitQueue.emplace(node->right, depth + 1); }
    }
    __builtin_unreachable();
  }

  // root == nullptrを特別扱いせずにdummyを使ってみる
  int minDepth2(TreeNode* root) {
    TreeNode dummy(0, root, nullptr);
    std::queue<std::tuple<TreeNode *, int>> visitQueue;
    visitQueue.emplace(&dummy, 0);
    while (!visitQueue.empty()) {
      auto [node, depth] = visitQueue.front();
      visitQueue.pop();
      if (node->left == nullptr && node->right == nullptr) { return depth; }
      if (node->left) { visitQueue.emplace(node->left, depth + 1); }
      if (node->right) { visitQueue.emplace(node->right, depth + 1); }
    }
    __builtin_unreachable();
  }

  // DFSでもやってみる
  // どちらにせよO(N)だが平衡に近い木ではだいぶ不利なはず
  int minDepth3(TreeNode* root) {
    auto dfs = [&](auto &&self, TreeNode *node) -> int {
      if (node == nullptr) { return 0; }
      int left = self(self, node->left);
      int right = self(self, node->right);
      if (left == 0) { return 1 + right; }
      if (right == 0) { return 1 + left; }
      return 1 + std::min(left, right);
    };
    return dfs(dfs, root);
  }
};
#endif // STEP2_HPP

