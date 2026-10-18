#include <vector>

using namespace std;

class Solution {
    long long MOD = 1e9 + 7;
    vector<vector<long long>> table;

    // Pascal's Triangle to precompute combinations (n Choose k)
    void buildPascalTable(int n) {
        table.assign(n + 1, vector<long long>(n + 1, 0));
        for (int i = 0; i <= n; ++i) {
            table[i][0] = 1;
            for (int j = 1; j <= i; ++j) {
                table[i][j] = (table[i - 1][j - 1] + table[i - 1][j]) % MOD;
            }
        }
    }

    long long dfs(const vector<int>& nums) {
        int m = nums.size();
        if (m <= 2) return 1;

        vector<int> left, right;
        int root = nums[0];

        for (int i = 1; i < m; ++i) {
            if (nums[i] < root) {
                left.push_back(nums[i]);
            } else {
                right.push_back(nums[i]);
            }
        }

        long long leftWays = dfs(left);
        long long rightWays = dfs(right);

        int L = left.size();
        int R = right.size();

        // Combination table[L + R][L] represents (L + R) choose L
        long long ways = (table[L + R][L] * leftWays) % MOD;
        ways = (ways * rightWays) % MOD;

        return ways;
    }

public:
    int numOfWays(vector<int>& nums) {
        int n = nums.size();
        buildPascalTable(n);
        
        // Subtract 1 to exclude the original ordering
        return (dfs(nums) - 1 + MOD) % MOD;
    }
};