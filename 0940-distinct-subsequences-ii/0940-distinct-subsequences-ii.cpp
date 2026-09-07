#include <string>
#include <vector>
#include <numeric>

class Solution {
public:
    int distinctSubseqII(std::string s) {
        int MOD = 1e9 + 7;
        // endWith[i] stores the total number of distinct subsequences ending with character ('a' + i)
        std::vector<long> endWith(26, 0);

        for (char c : s) {
            // Calculate the current sum of all subsequences
            long currentSum = 0;
            for (long count : endWith) {
                currentSum = (currentSum + count) % MOD;
            }

            // Subsequences ending with character 'c' equals:
            // 1 (the single-character subsequence 'c') + total existing subsequences
            endWith[c - 'a'] = (currentSum + 1) % MOD;
        }

        // Sum up distinct subsequences ending with all 26 characters
        long total = 0;
        for (long count : endWith) {
            total = (total + count) % MOD;
        }

        return total;
    }
};