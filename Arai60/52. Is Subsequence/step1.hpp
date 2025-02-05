#ifndef STEP1_HPP
#define STEP1_HPP

/*
  何がわからなかったか
   - N/A
  何を考えて解いていたか
   - tを前から舐めていけばいい
  正解してから気づいたこと
   - Follow upに対応するためには、tを毎回舐めると無駄なので、前処理をしておいて
     ある文字がtのなかのどこにあるかを高速に調べられるようにしておくといい
*/
#include <string>

class Solution {
public:
  // Naive solution
  bool isSubsequence(const std::string &subsequence, const std::string &text) {
    if (subsequence.empty()) {
      return true;
    }
    size_t i = 0;
    for (auto c : text) {
      if (subsequence[i] == c) {
        ++i;
        if (subsequence.size() == i) {
          return true;
        }
      }
    }
    return false;
  }
};

#endif // STEP1_HPP
