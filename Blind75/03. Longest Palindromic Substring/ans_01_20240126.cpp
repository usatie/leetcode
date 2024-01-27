#include <string>
using namespace std;

class Solution {
public:
    string longestPalindrome(string s) {
        string longest;
        int next = 0;
        while (next < s.size()) {
            // s[l...r] is a palindrome (inclusive)
            int l = next;
            int r = next;
            while (r+1 < s.size() && s[l] == s[r+1]) r++;
            next = r + 1; // next i start from different character
            while (l-1 >= 0 && r+1 < s.size() && s[l-1] == s[r+1]) {
                l--;
                r++;
            }
            int len = r - l + 1;
            if (longest.size() < len) {
                longest = s.substr(l, len);
            }
        }
        return longest;
    }
};
