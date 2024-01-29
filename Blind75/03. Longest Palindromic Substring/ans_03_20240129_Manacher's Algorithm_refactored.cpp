#include <string>
#include <vector>
using namespace std;

class Manacher {
    public:
        const string &original;
        string bogus;
        vector<int> palindromeRadii;
        Manacher(const string &s): original(s), palindromeRadii(s.size() * 2 + 1, 0) {
            bogus = "|";
            for (auto c : s) {
                bogus += c;
                bogus += "|";
            }
        }
        bool hasRoomOnLeft(const string &s, int center, int radius) {
            return center - radius - 1 >= 0;
        }
        bool hasRoomOnRight(const string &s, int center, int radius) {
            return center + radius + 1 < s.size();
        }
        bool isNextRadiiEqual(const string &s, int center, int radius) {
            return s[center-radius-1] == s[center+radius+1];
        }
        // Determine the longest palindrome starting
        // at Center-Radius and going to Center+Radius
        int findLongestOnCenter(const string &s, int center, int radius) {
            while (hasRoomOnLeft(s, center, radius)
                && hasRoomOnRight(s, center, radius)
                && isNextRadiiEqual(s, center, radius)) {
                ++radius;
            }
            return radius;
        }

        void updateLongestPalindromes() {
            int radius = 0;
            int center = 0;
            while (center < bogus.size()) {
                palindromeRadii[center] = findLongestOnCenter(bogus, center, radius);
                int distance = 1;
                auto nextCenter = [&] () { return center + distance; };
                int nextRadius = 0;
                while (distance < palindromeRadii[center]) {
                    int mirroredCenter = center - distance;
                    int mirroredCenterRadius = palindromeRadii[mirroredCenter];
                    int maxMirroredCenterRadius = palindromeRadii[center] - distance;
                    if (mirroredCenterRadius < maxMirroredCenterRadius) {
                        palindromeRadii[nextCenter()] = mirroredCenterRadius;
                        ++distance;
                    } else if (mirroredCenterRadius > maxMirroredCenterRadius) {
                        palindromeRadii[nextCenter()] = maxMirroredCenterRadius;
                        ++distance;
                    } else {
                        nextRadius = maxMirroredCenterRadius;
                        break;
                    }
                }
                center = nextCenter();
                radius = nextRadius;
            }
        }

        string findLongestPalindrome() {
            auto begin = palindromeRadii.begin();
            auto end = palindromeRadii.end();
            auto maxRadiusIt = max_element(begin, end);
            int center = maxRadiusIt - begin;
            int radius = *maxRadiusIt;
            int pos = (center - radius) / 2;
            return original.substr(pos, radius);
        }
};

class Solution {
public:
    string longestPalindrome(string s) {
        // Manacher's Algorithm
        Manacher manacher(s);
        manacher.updateLongestPalindromes();
        return manacher.findLongestPalindrome();
    }
};
