#include <algorithm> // min, max
#include <vector> // vector
using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int area = 0;
        int left = 0, right = height.size() - 1;
        while (left < right) {
            int w = right - left;
            int h = min(height[left], height[right]);
            area = max(area, w * h);
            while (left < right && height[left] <= h) ++left;
            while (left < right && height[right] <= h) --right;
        }
        return area;
    }
};
