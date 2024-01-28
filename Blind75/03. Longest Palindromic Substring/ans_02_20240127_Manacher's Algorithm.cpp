#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    string longestPalindrome(string s) {
        // Manacher's Algorithm
        string ss = "|";
        for (auto c : s) {
            ss += c;
            ss += "|";
        }
        int center = 0;
        int radius = 0;
        vector<int> maxRadii(ss.size(), 0);
        while (center < ss.size()) {
            while (center - (radius+1) >= 0
                && center + (radius+1) < ss.size()
                && ss[center-(radius+1)] == ss[center+(radius+1)]) {
                    ++radius;
            }
            maxRadii[center] = radius;
            int oldCenter = center;
            int oldRadius = radius;
            radius = 0;
            ++center;
            while (center < oldCenter + oldRadius) {
                int mirroredCenter = oldCenter - (center - oldCenter);
                int maxMirroredRadius = oldRadius - (center - oldCenter);
                if (maxRadii[mirroredCenter] < maxMirroredRadius) {
                    maxRadii[center] = maxRadii[mirroredCenter];
                    ++center;
                } else if (maxRadii[mirroredCenter] > maxMirroredRadius) {
                    maxRadii[center] = maxMirroredRadius;
                    ++center;
                } else {
                    radius = maxMirroredRadius;
                    break;
                }
            }
        }
        string longest;
        for (int center = 0; center < ss.size(); ++center) {
            int radius = maxRadii[center];
            if (longest.size() < radius) {
                longest = s.substr((center-radius)/2, radius);
            }
        }
        return longest;
    }
};

