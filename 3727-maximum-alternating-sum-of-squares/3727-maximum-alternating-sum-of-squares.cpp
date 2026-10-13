#include <vector>
#include <cmath>
#include <algorithm>

class Solution {
public:
    long long maxAlternatingSum(std::vector<int>& nums) {
        int n = nums.size();
        
        // Sort elements based on their squared values in ascending order
        std::sort(nums.begin(), nums.end(), [](int a, int b) {
            return (long long)a * a < (long long)b * b;
        });

        long long score = 0;
        
        // Place the smallest squares into negative positions 
        // and the largest squares into positive positions
        int left = 0;
        int right = n - 1;
        bool positive = true;

        while (left <= right) {
            if (positive) {
                // Pick the largest remaining square for the positive term
                long long val = nums[right--];
                score += val * val;
            } else {
                // Pick the smallest remaining square for the negative term
                long long val = nums[left++];
                score -= val * val;
            }
            positive = !positive; // Alternate signs
        }

        return score;
    }
};