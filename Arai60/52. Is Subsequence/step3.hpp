/*
  3問連続で正解するのにかかった時間 : 6:30
  subsequence.size() : M
  text.size() : N
  時間計算量: O(N + kMlogN)
  空間計算量: O(N)
*/
#ifndef STEP3_HPP
#define STEP3_HPP

#include <map>
#include <string>
#include <vector>

class Solution {
private:
  std::map<char, std::vector<int>> character_positions;

public:
  bool isSubsequence(const std::string &subsequence, const std::string &text) {
    if (character_positions.empty()) {
      for (size_t i = 0; i < text.size(); ++i) {
        char c = text[i];
        character_positions[c].push_back(i);
      }
    }
    size_t search_pos = 0;
    for (char c : subsequence) {
      auto &positions = character_positions[c];
      auto found =
          std::lower_bound(positions.begin(), positions.end(), search_pos);
      if (found == positions.end()) {
        return false;
      }
      search_pos = *found + 1;
    }
    return true;
  }
};

#endif // STEP3_HPP
