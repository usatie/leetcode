/*
 講師陣はどのようなコメントを残すだろうか？
  -
 他の人のコードを読んで考えたこと
  - https://github.com/philip82148/leetcode-arai60/pull/7
    関数プロトタイプとかは与えられたものと考えるのではなく、より好ましいものに
    変えちゃった方がいい
  - https://github.com/Yoshiki-Iwasa/Arai60/pull/62
    Edit distanceの問題として捉えることもできるのか.
    https://en.wikipedia.org/wiki/Levenshtein_distance
    DPでも解ける, なるほどやってみよう
 改善する時にかんがえたこと
  - 同じtextに対してqueryが来ないなら初期化したcharacterPositionsをメンバ変数で
    持ってもいいし、Constructorで初期化してもいい。
  - Constructorで初期化する場合関数プロトタイプが変わってテストをそのためだけに
    書き直したり用意するのが面倒なのでここではやってない。
  - 複数のtextに対してsubsequenceをチェックする場合、textごとに初期化する。
    ただし、textが大きい場合はmapのkeyとしてtextも保存する羽目になるので、
    メモリを食ってしまうかもしれない。衝突を許容して少ない数のtextだったら
    key自体もhashにしてしまってもいいかもしれない?
  - `auto positions = characterPositions[c];`と元々はしていたけれど
    referenceにしておかないと意図せぬcopyが発生してしまう
*/
#ifndef STEP2_HPP
#define STEP2_HPP

#include <functional>
#include <map>
#include <set>
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
    std::map<char, std::set<size_t>> characterPositions;
    for (size_t i = 0; i < text.size(); ++i) {
      char c = text[i];
      // characterPositions[c].emplace(i);
      auto &positions = characterPositions[c];
      positions.insert(positions.end(), i);
    }
    size_t searchPos = 0;
    for (char c : subsequence) {
      auto &positions = characterPositions[c];
      auto found = positions.lower_bound(searchPos);
      if (found == positions.end()) {
        return false;
      }
      searchPos = *found + 1;
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
      auto &positions = characterPositions[c];
      auto found =
          std::lower_bound(positions.begin(), positions.end(), searchPos);
      if (found == positions.end()) {
        return false;
      }
      searchPos = *found + 1;
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
      auto &positions = characterPositions[c];
      auto found =
          std::lower_bound(positions.begin(), positions.end(), searchPos);
      if (found == positions.end()) {
        return false;
      }
      searchPos = *found + 1;
    }
    return true;
  }
};

// Dynamic Programming
class Solution4 {
public:
  bool isSubsequence(const std::string &subsequence, const std::string &text) {
    size_t m = subsequence.size();
    size_t n = text.size();
    // is_subseq[i][j] : subsequence[0..i) is a subsequence of text[0..j)
    std::vector<std::vector<bool>> is_subseq(m + 1,
                                             std::vector<bool>(n + 1, false));
    for (size_t j = 0; j <= n; ++j) {
      is_subseq[0][j] = true;
    }
    for (size_t i = 1; i <= m; ++i) {
      for (size_t j = 1; j <= n; ++j) {
        if (subsequence[i - 1] == text[j - 1]) {
          is_subseq[i][j] = is_subseq[i - 1][j - 1];
        } else {
          is_subseq[i][j] = is_subseq[i][j - 1];
        }
      }
    }
    return is_subseq[m][n];
  }
};

// Recursive
class Solution5 {
public:
  // ラムダでの再帰関数がうまく書けなくて、std::functionを使うことになった
  // 書ける場合と書けない場合の違いは何だろうか？
  bool isSubsequence(const std::string &subsequence, const std::string &text) {
    std::function<bool(size_t, size_t)> is_subseq = [&](size_t i,
                                                        size_t j) -> bool {
      if (i == 0) {
        return true;
      }
      if (j == 0) {
        return false;
      }
      if (subsequence[i - 1] == text[j - 1]) {
        return is_subseq(i - 1, j - 1);
      } else {
        return is_subseq(i, j - 1);
      }
    };
    return is_subseq(subsequence.size(), text.size());
  }
};

// C++17 way to write recursive lambda
// Recursive (Lambda), only works with C++17
// If auto is used as a type of a parameter or an explicit template parameter
// list is provided(since C++20), the lambda is a generic lambda. (since C++14)
// https://en.cppreference.com/w/cpp/language/lambda
class Solution6 {
public:
  // 引数で自身を渡してあげれば書けるというのがC++17の機能だった模様
  // というか、引数でautoを使える(=Generic Lambda)のがC++17から
  // https://github.com/usatie/leetcode/pull/4/files#diff-43e2749181b31eb4f4bf1fd95048e0d7f2fb65e9b44c84eefaf3905a22349a90R77
  //
  // `auto &&self`というのはどこからか引っ張ってきたコードだったけど、
  // `auto self`でも`auto &&self`でも動いた. それぞれの挙動の違いが違いが
  // わかっていない. `&`にしないと関数オブジェクト?のコピーが発生するのはわかる
  // 気がするが`&&`は普段使ったことがない. また、cppreferenceのサンプルコードも
  // `auto`だったので、referenceにする必要があるのかもわからない
  // https://stackoverflow.com/questions/29859796/c-auto-vs-auto
  //
  // ChatGPT-o3-mini-highに質問してみて、だんだんと違いがわかってきた。
  // 色々と理解が曖昧なものがあったが、さらにドキュメントを読む必要がありそう
  // lvalue, rvalue, move constructor, move semantics, perfect forwarding,
  // type erasure, std::function
  // https://chatgpt.com/share/67a67173-839c-8000-913d-ca67b6aa6859
  //
  // たくさんあるのでひとまず積読ですが、徐々に読んでみます。
  // https://chatgpt.com/share/67a67173-839c-8000-913d-ca67b6aa6859
  // https://en.cppreference.com/w/cpp/language/auto
  // https://en.cppreference.com/w/cpp/language/reference
  // https://en.cppreference.com/w/cpp/language/value_category
  // https://en.cppreference.com/w/cpp/utility/move
  // https://en.cppreference.com/w/cpp/language/move_constructor
  // https://en.cppreference.com/w/cpp/language/move_assignment
  // https://en.cppreference.com/w/cpp/utility/forward
  // https://en.cppreference.com/w/cpp/utility/functional/function
  //
  // Type Erasure
  // https://cplusplus.com/articles/oz18T05o/
  // https://davekilian.com/cpp-type-erasure.html
  bool isSubsequence(const std::string &subsequence, const std::string &text) {
    auto is_subseq = [&](auto &&self, size_t i, size_t j) -> bool {
      if (i == 0) {
        return true;
      }
      if (j == 0) {
        return false;
      }
      if (subsequence[i - 1] == text[j - 1]) {
        return self(self, i - 1, j - 1);
      } else {
        return self(self, i, j - 1);
      }
    };
    return is_subseq(std::move(is_subseq), subsequence.size(), text.size());
  }
};

// C++23 way to write recursive lambda
// https://en.cppreference.com/w/cpp/language/member_functions#Explicit_object_member_functions
class Solution7 {
public:
  bool isSubsequence(const std::string &subsequence, const std::string &text) {
    auto is_subseq = [&](this auto self, size_t i, size_t j) -> bool {
      if (i == 0) {
        return true;
      }
      if (j == 0) {
        return false;
      }
      if (subsequence[i - 1] == text[j - 1]) {
        return self(i - 1, j - 1);
      } else {
        return self(i, j - 1);
      }
    };
    return is_subseq(subsequence.size(), text.size());
  }
};
#endif // STEP2_HPP
