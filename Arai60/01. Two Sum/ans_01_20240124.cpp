#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hash;
        for (int i = 0; i < nums.size(); ++i) {
            int rest = target - nums[i];
            if (hash.find(rest) != hash.end()) {
                return vector<int>({i, hash[rest]});
            }
            hash[nums[i]] = i;
        }
        return vector<int>();
    }
};
