#include <algorithm>
#include <numeric>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1)
            return s;
        int cycle = numRows * 2 - 2;
        vector<string> rows(numRows);
        for (int i = 0; i < s.size(); ++i) {
            int modulo = i % cycle;
            int row = min(modulo, cycle - modulo);
            rows[row] += s[i];
        }
        return accumulate(rows.begin(), rows.end(), string());
    }
};
