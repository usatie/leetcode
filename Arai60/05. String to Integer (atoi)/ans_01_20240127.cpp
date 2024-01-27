#include <ctype.h> // isdigit
#include <limits.h> // INT_MIN, INT_MAX
#include <string> // string
using namespace std;

class Solution {
public:
    int myAtoi(string s) {
        auto it = s.begin();
        // whitespace
        while (it != s.end() && *it == ' ') { ++it; }
        // sign
        bool isNegative = false;
        if (it != s.end()) {
            if (*it == '-') { isNegative = true; ++it; }
            else if (*it == '+') { ++it; }
        }
        // digits
        int val = 0;
        for (; it != s.end() && isdigit(*it); ++it) {
            int digit = *it - '0';
            // carry
            if (val < INT_MIN / 10) return INT_MIN;
            else if (val > INT_MAX / 10) return INT_MAX;
            val *= 10;
            // sub/add
            if (isNegative) {
                if (val < INT_MIN + digit) return INT_MIN;
                val -= digit;
            } else {
                if (val > INT_MAX - digit) return INT_MAX;
                val += digit;
            }
        }
        return val;
    }
};
