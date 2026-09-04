#include <vector>
#include <algorithm>

class Solution {
public:
    int firstStableIndex(std::vector<int>& nums, int k) {
        int n = nums.size();
        std::vector<long long> suffix_min(n);
        
        // Step 1: Precompute suffix minimums
        suffix_min[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            suffix_min[i] = std::min((long long)nums[i], suffix_min[i + 1]);
        }
        
        // Step 2: Traverse from left to right tracking prefix maximum
        long long prefix_max = nums[0];
        for (int i = 0; i < n; ++i) {
            prefix_max = std::max(prefix_max, (long long)nums[i]);
            
            long long instability_score = prefix_max - suffix_min[i];
            if (instability_score <= k) {
                return i; // First stable index found
            }
        }
        
        return -1; // No stable index exists
    }
};