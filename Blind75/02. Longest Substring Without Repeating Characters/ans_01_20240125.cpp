#include <string>
#include <vector>
using namespace std;

class Solution {
private:
    int max(int a, int b) {
        return a > b ? a : b;
    }
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> seen(256, -1);
        int start = -1;
        int longest = 0;
        for (int i = 0; i < s.size(); ++i) {
            unsigned char c = s[i];
            start = max(start, seen[c]);
            seen[c] = i;
            longest = max(longest, i - start);
        }
        return longest;
    }
};
