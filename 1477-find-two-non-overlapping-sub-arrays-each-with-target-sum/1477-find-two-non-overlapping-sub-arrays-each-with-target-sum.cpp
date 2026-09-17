#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();
        vector<int> min_len(n, INT_MAX);
        
        int left = 0;
        int current_sum = 0;
        int ans = INT_MAX;
        int min_so_far = INT_MAX;
        
        for (int right = 0; right < n; ++right) {
            current_sum += arr[right];
            
            // Shrink window if sum exceeds target
            while (current_sum > target) {
                current_sum -= arr[left];
                left++;
            }
            
            // Valid sub-array found
            if (current_sum == target) {
                int curr_len = right - left + 1;
                
                // If there's a valid non-overlapping sub-array to the left
                if (left > 0 && min_len[left - 1] != INT_MAX) {
                    ans = min(ans, curr_len + min_len[left - 1]);
                }
                
                min_so_far = min(min_so_far, curr_len);
            }
            
            // Update DP state for index `right`
            min_len[right] = min_so_far;
        }
        
        return ans == INT_MAX ? -1 : ans;
    }
};