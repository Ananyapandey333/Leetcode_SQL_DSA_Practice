#include <vector>

class Solution {
public:
    std::vector<long long> resultArray(std::vector<int>& nums, int k) {
        std::vector<long long> result(k, 0);
        // dp[r] stores the count of subarrays ending at the current element 
        // that have a product % k == r
        std::vector<long long> dp(k, 0);
        
        for (int num : nums) {
            std::vector<long long> next_dp(k, 0);
            int rem = num % k;
            
            // 1. Single element subarray consisting of just 'num'
            next_dp[rem]++;
            
            // 2. Extend existing subarrays from previous step
            for (int r = 0; r < k; ++r) {
                if (dp[r] > 0) {
                    int next_rem = (r * rem) % k;
                    next_dp[next_rem] += dp[r];
                }
            }
            
            // 3. Add counts of subarrays ending at current index to total result
            for (int r = 0; r < k; ++r) {
                result[r] += next_dp[r];
            }
            
            // Move to next step
            dp = std::move(next_dp);
        }
        
        return result;
    }
};