#include <vector>
#include <numeric>
#include <algorithm>

class Solution {
private:
    // Helper function to calculate the sum of digits of a number
    int getDigitSum(int val) {
        int sum = 0;
        while (val > 0) {
            sum += val % 10;
            val /= 10;
        }
        return sum;
    }

public:
    int minSwaps(std::vector<int>& nums) {
        int n = nums.size();
        
        // Pair each number with its digit sum and original index
        struct Element {
            int value;
            int digitSum;
            int originalIdx;
        };
        
        std::vector<Element> arr(n);
        for (int i = 0; i < n; ++i) {
            arr[i] = {nums[i], getDigitSum(nums[i]), i};
        }
        
        // Sort based on digit sum, breaking ties with the value itself
        std::sort(arr.begin(), arr.end(), [](const Element& a, const Element& b) {
            if (a.digitSum != b.digitSum) {
                return a.digitSum < b.digitSum;
            }
            return a.value < b.value;
        });
        
        // Traverse permutation cycles to find total swaps
        std::vector<bool> visited(n, false);
        int totalSwaps = 0;
        
        for (int i = 0; i < n; ++i) {
            // Skip if already placed or visited
            if (visited[i] || arr[i].originalIdx == i) {
                continue;
            }
            
            // Measure cycle length
            int cycleSize = 0;
            int curr = i;
            
            while (!visited[curr]) {
                visited[curr] = true;
                curr = arr[curr].originalIdx;
                cycleSize++;
            }
            
            if (cycleSize > 1) {
                totalSwaps += (cycleSize - 1);
            }
        }
        
        return totalSwaps;
    }
};