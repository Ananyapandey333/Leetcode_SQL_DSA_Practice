#include <vector>

class Solution {
public:
    int sortPermutation(std::vector<int>& nums) {
        int k = -1; // Marker for the first misplaced element
        
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] != i) {
                if (k == -1) {
                    k = nums[i];
                } else {
                    k &= nums[i];
                }
            }
        }
        
        // If all elements are already in their correct positions
        return (k == -1) ? 0 : k;
    }
};