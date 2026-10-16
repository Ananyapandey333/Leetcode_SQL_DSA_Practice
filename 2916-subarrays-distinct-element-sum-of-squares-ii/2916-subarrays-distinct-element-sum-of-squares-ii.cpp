#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
    static const int MOD = 1e9 + 7;
    
    struct Node {
        long long sumD = 0;
        long long sumD2 = 0;
        long long lazy = 0;
    };
    
    vector<Node> tree;

    void push(int node, int start, int end) {
        if (tree[node].lazy == 0) return;
        
        long long val = tree[node].lazy;
        int mid = start + (end - start) / 2;
        int leftLen = mid - start + 1;
        int rightLen = end - mid;

        // Apply lazy update to left child
        tree[2 * node].sumD2 = (tree[2 * node].sumD2 + 2 * val * tree[2 * node].sumD + val * val % MOD * leftLen) % MOD;
        tree[2 * node].sumD = (tree[2 * node].sumD + val * leftLen) % MOD;
        tree[2 * node].lazy = (tree[2 * node].lazy + val) % MOD;

        // Apply lazy update to right child
        tree[2 * node + 1].sumD2 = (tree[2 * node + 1].sumD2 + 2 * val * tree[2 * node + 1].sumD + val * val % MOD * rightLen) % MOD;
        tree[2 * node + 1].sumD = (tree[2 * node + 1].sumD + val * rightLen) % MOD;
        tree[2 * node + 1].lazy = (tree[2 * node + 1].lazy + val) % MOD;

        tree[node].lazy = 0;
    }

    void update(int node, int start, int end, int l, int r, long long val) {
        if (r < start || end < l) return;
        if (l <= start && end <= r) {
            int len = end - start + 1;
            tree[node].sumD2 = (tree[node].sumD2 + 2 * val * tree[node].sumD + val * val % MOD * len) % MOD;
            tree[node].sumD = (tree[node].sumD + val * len) % MOD;
            tree[node].lazy = (tree[node].lazy + val) % MOD;
            return;
        }
        
        push(node, start, end);
        int mid = start + (end - start) / 2;
        update(2 * node, start, mid, l, r, val);
        update(2 * node + 1, mid + 1, end, l, r, val);
        
        tree[node].sumD = (tree[2 * node].sumD + tree[2 * node + 1].sumD) % MOD;
        tree[node].sumD2 = (tree[2 * node].sumD2 + tree[2 * node + 1].sumD2) % MOD;
    }

public:
    int sumCounts(vector<int>& nums) {
        int n = nums.size();
        tree.assign(4 * n, Node());
        
        unordered_map<int, int> last_seen;
        long long total_ans = 0;

        for (int j = 0; j < n; ++j) {
            int prev = last_seen.count(nums[j]) ? last_seen[nums[j]] : -1;
            
            // Increment distinct count for all subarrays starting in range [prev + 1, j]
            update(1, 0, n - 1, prev + 1, j, 1);
            
            // Add current total sum of squares of distinct counts to total_ans
            total_ans = (total_ans + tree[1].sumD2) % MOD;
            
            last_seen[nums[j]] = j;
        }

        return (total_ans % MOD + MOD) % MOD;
    }
};