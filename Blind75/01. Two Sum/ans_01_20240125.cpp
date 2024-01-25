#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> value_to_index;
        for (int i = 0; i < nums.size(); ++i) {
            int rest = target - nums[i];
            if (value_to_index.find(rest) != value_to_index.end()) {
                return vector<int>({i, value_to_index[rest]});
            }
            value_to_index[nums[i]] = i;
        }
        return vector<int>();
    }
};
