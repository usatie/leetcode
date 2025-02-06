/*
 講師陣はどのようなコメントを残すだろうか？
  -
 他の人のコードを読んで考えたこと
  -
 改善する時にかんがえたこと
  - 同じtextに対してqueryが来ないなら初期化したcharacterPositionsをメンバ変数で
    持ってもいいし、Constructorで初期化してもいい。
  - Constructorで初期化する場合関数プロトタイプが変わってテストをそのためだけに
    書き直したり用意するのが面倒なのでここではやってない。
  - 複数のtextに対してsubsequenceをチェックする場合、textごとに初期化する。
    ただし、textが大きい場合はmapのkeyとしてtextも保存する羽目になるので、
    メモリを食ってしまうかもしれない。衝突を許容して少ない数のtextだったら
    key自体もhashにしてしまってもいいかもしれない?
*/
#ifndef STEP2_HPP
#define STEP2_HPP

#include <map>
#include <string>
#include <vector>

class Solution1 {
  // Follow up
  /* Suppose there are lots of incoming s, say s1, s2, ..., sk where k >= 109,
   * and you want to check one by one to see if t has its subsequence. In this
   * scenario, how would you change your code?
   */
public:
  bool isSubsequence(const std::string &subsequence, const std::string &text) {
    std::map<char, std::vector<size_t>> characterPositions;
    for (size_t i = 0; i < text.size(); ++i) {
      char c = text[i];
      characterPositions[c].push_back(i);
    }
    size_t searchPos = 0;
    for (char c : subsequence) {
      auto positions = characterPositions[c];
      auto found =
          std::lower_bound(positions.begin(), positions.end(), searchPos);
      if (found == positions.end()) {
        return false;
      }
      searchPos = *found;
    }
    return true;
  }
};

// If text is the same all the time, we only need to initialize the data once.
class Solution2 {
private:
  std::map<char, std::vector<size_t>> characterPositions;

public:
  bool isSubsequence(const std::string &subsequence, const std::string &text) {
    if (characterPositions.empty()) {
      for (size_t i = 0; i < text.size(); ++i) {
        char c = text[i];
        characterPositions[c].push_back(i);
      }
    }
    size_t searchPos = 0;
    for (char c : subsequence) {
      auto positions = characterPositions[c];
      auto found =
          std::lower_bound(positions.begin(), positions.end(), searchPos);
      if (found == positions.end()) {
        return false;
      }
      searchPos = *found;
    }
    return true;
  }
};

// If we expect multiple but small texts, and massive subsequence queries,
// we can initialize the data for each text.
class Solution3 {
private:
  typedef std::map<char, std::vector<size_t>> character_positions_t;
  std::map<std::string, character_positions_t> initialized_data;
  void initialize(const std::string &text) {
    auto &characterPositions = initialized_data[text];
    for (size_t i = 0; i < text.size(); ++i) {
      char c = text[i];
      characterPositions[c].push_back(i);
    }
  }

public:
  bool isSubsequence(const std::string &subsequence, const std::string &text) {
    if (initialized_data.count(text) == 0) {
      initialize(text);
    }
    auto &characterPositions = initialized_data[text];
    size_t searchPos = 0;
    for (char c : subsequence) {
      auto positions = characterPositions[c];
      auto found =
          std::lower_bound(positions.begin(), positions.end(), searchPos);
      if (found == positions.end()) {
        return false;
      }
      searchPos = *found;
    }
    return true;
  }
};

#endif // STEP2_HPP
