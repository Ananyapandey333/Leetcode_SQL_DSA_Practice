#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        int n = nums1.size();
        long long total_k = (long long)k1 + k2;
        int max_diff = 0;
        vector<int> diffs(n);
        for (int i = 0; i < n; ++i) {
            diffs[i] = abs(nums1[i] - nums2[i]);
            max_diff = max(max_diff, diffs[i]);
        }
        vector<long long> count(max_diff + 1, 0);
        for (int d : diffs) {
            count[d]++;
        }
        for (int d = max_diff; d > 0 && total_k > 0; --d) {
            if (count[d] == 0) continue;
            
            long long ops_needed = count[d];
            
            if (total_k >= ops_needed) {
                total_k -= ops_needed;
                count[d - 1] += ops_needed;
                count[d] = 0;
            } else {
                count[d - 1] += total_k;
                count[d] -= total_k;
                total_k = 0;
            }
        }
        long long min_sum = 0;
        for (long long d = 1; d <= max_diff; ++d) {
            if (count[d] > 0) {
                min_sum += count[d] * d * d;
            }
        }
        
        return min_sum;
    }
};