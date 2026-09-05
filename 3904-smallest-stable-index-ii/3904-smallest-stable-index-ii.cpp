#include <vector>
#include <algorithm>

class Solution {
public:
    int firstStableIndex(std::vector<int>& nums, int k) {
        int n = nums.size();
        if (n == 0) return -1;

        std::vector<int> pref_max(n);
        std::vector<int> suff_min(n);

        // Compute prefix maximums
        pref_max[0] = nums[0];
        for (int i = 1; i < n; ++i) {
            pref_max[i] = std::max(pref_max[i - 1], nums[i]);
        }

        // Compute suffix minimums
        suff_min[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            suff_min[i] = std::min(suff_min[i + 1], nums[i]);
        }

        // Find the first index where instability score <= k
        for (int i = 0; i < n; ++i) {
            long long instability_score = (long long)pref_max[i] - suff_min[i];
            if (instability_score <= k) {
                return i;
            }
        }

        return -1;
    }
};