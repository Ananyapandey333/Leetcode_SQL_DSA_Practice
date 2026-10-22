#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return 0;

        // Find the index of 0
        int idx = 0;
        for (int i = 0; i < n; ++i) {
            if (nums[i] == 0) {
                idx = i;
                break;
            }
        }

        bool is_forward = true;
        bool is_reverse = true;

        // Check if array is in forward cyclic order: nums[i] == (nums[0] + i) % n
        for (int i = 0; i < n; ++i) {
            if (nums[i] != (nums[0] + i) % n) {
                is_forward = false;
                break;
            }
        }

        // Check if array is in reverse cyclic order: nums[i] == (nums[0] - i + n) % n
        for (int i = 0; i < n; ++i) {
            if (nums[i] != (nums[0] - i + n) % n) {
                is_reverse = false;
                break;
            }
        }

        if (is_forward) {
            return min(idx, n - idx + 2);
        }
        
        if (is_reverse) {
            return min(n - idx, idx + 2);
        }

        return -1;
    }
};