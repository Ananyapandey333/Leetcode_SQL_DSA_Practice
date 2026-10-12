#include <vector>

class Solution {
public:
    int maxSum(std::vector<int>& nums, int k) {
        long long MOD = 1e9 + 7;
        
        // Array to store how many times each of the 30 bits is set to 1.
        std::vector<int> bit_counts(30, 0);
        
        // Loop through every number in nums to count set bits
        for (int num : nums) {
            for (int b = 0; b < 30; ++b) {
                // Check if the b-th bit of num is 1
                if ((num >> b) & 1) {
                    bit_counts[b]++; // Increase count for bit b
                }
            }
        }
        
        long long total_sum = 0;
        
        // We only need to make the top 'k' largest possible numbers
        for (int i = 0; i < k; ++i) {
            long long current_num = 0;
            
            // Try to set every bit 'b' for the current number
            for (int b = 0; b < 30; ++b) {
                if (bit_counts[b] > 0) {
                    current_num |= (1LL << b); // Add 2^b to current_num
                    bit_counts[b]--;           // Use up one '1' for bit b
                }
            }
            
            // Calculate current_num^2 modulo 10^9 + 7
            long long square = (current_num % MOD) * (current_num % MOD) % MOD;
            
            // Add the square to our answer
            total_sum = (total_sum + square) % MOD;
        }
        
        return total_sum;
    }
};