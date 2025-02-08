#include <iostream>
#include <string>

#include "step2.hpp"

#define test(subsequence, text, expected)                                      \
  [] {                                                                         \
    bool actual = Solution7().isSubsequence(subsequence, text);                \
    std::cout << "Test: " << #subsequence << " in " << #text << "\" : ";       \
    if (actual == expected) {                                                  \
      std::cout << "OK" << std::endl;                                          \
    } else {                                                                   \
      std::cout << "Failed" << std::endl                                       \
                << "Expected: " << expected << ", but got: " << actual         \
                << std::endl;                                                  \
    }                                                                          \
  }()

int main(void) {
  test("abc", "ahbgdc", true);
  test("axc", "ahbgdc", false);
  test("", "ahbgdc", true);
  test("a", "", false);
}
