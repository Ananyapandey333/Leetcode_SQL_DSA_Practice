#include <vector>
#include <algorithm>
#include <numeric>

class Solution {
public:
    int sortableIntegers(std::vector<int>& nums) {
        int n = nums.size();
        
        // Target globally sorted array
        std::vector<int> sorted_nums = nums;
        std::sort(sorted_nums.begin(), sorted_nums.end());

        int total_sum = 0;

        for (int k = 1; k <= n; ++k) {
            if (n % k != 0) continue;

            bool is_sortable = true;

            for (int i = 0; i < n; i += k) {
                // Find the starting offset in nums[i ... i+k-1] that corresponds
                // to the minimum element matching sorted_nums[i].
                
                // 1. Count the number of drops (where nums[j] > nums[j+1])
                int drops = 0;
                int drop_idx = -1;
                for (int j = 0; j < k; ++j) {
                    int curr = nums[i + j];
                    int next = nums[i + (j + 1) % k];
                    if (curr > next) {
                        drops++;
                        drop_idx = (j + 1) % k;
                    }
                }

                // A valid rotated sorted block can have at most 1 drop
                if (drops > 1) {
                    is_sortable = false;
                    break;
                }

                // Determine the starting index after rotation
                int start_offset = (drops == 0) ? 0 : drop_idx;

                // 2. Verify that the rotated sequence matches sorted_nums[i ... i+k-1]
                for (int j = 0; j < k; ++j) {
                    if (nums[i + (start_offset + j) % k] != sorted_nums[i + j]) {
                        is_sortable = false;
                        break;
                    }
                }

                if (!is_sortable) break;
            }

            if (is_sortable) {
                total_sum += k;
            }
        }

        return total_sum;
    }
};