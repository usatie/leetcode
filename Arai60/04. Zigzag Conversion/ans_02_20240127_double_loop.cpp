#include <numeric> // accumulate
#include <string> // string
#include <vector> // vector
using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1)
            return s;
        vector<string> rows(numRows);
        int i = 0;
        bool increasing = true;
        while (i < s.size()) {
            int row = 0;
            // [0, numRows-1)
            while (i < s.size() && row < numRows - 1) {
                rows[row] += s[i];
                ++row;
                ++i;
            }
            // [numRows-1, 0)
            while (i < s.size() && row > 0) {
                rows[row] += s[i];
                --row;
                ++i;
            }
        }
        return accumulate(rows.begin(), rows.end(), string());
    }
};
