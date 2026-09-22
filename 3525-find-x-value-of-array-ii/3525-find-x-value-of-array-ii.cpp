#include <vector>

using namespace std;

struct Node {
    int prod;
    int cnt[5];

    Node() {
        prod = 1;
        for (int i = 0; i < 5; ++i) cnt[i] = 0;
    }
};

class Solution {
    int k;
    vector<Node> tree;

    Node merge(const Node& left, const Node& right) {
        Node res;
        res.prod = (left.prod * right.prod) % k;
        
        // Include prefix counts from the left child
        for (int r = 0; r < k; ++r) {
            res.cnt[r] = left.cnt[r];
        }

        // Include prefix counts from the right child, transformed by left's full product
        for (int r = 0; r < k; ++r) {
            if (right.cnt[r] > 0) {
                int new_r = (left.prod * r) % k;
                res.cnt[new_r] += right.cnt[r];
            }
        }
        return res;
    }

    void build(int node, int start, int end, const vector<int>& nums) {
        if (start == end) {
            int val = nums[start] % k;
            tree[node].prod = val;
            tree[node].cnt[val] = 1;
            return;
        }
        int mid = start + (end - start) / 2;
        build(2 * node, start, mid, nums);
        build(2 * node + 1, mid + 1, end, nums);
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            int rem = val % k;
            tree[node].prod = rem;
            for (int r = 0; r < k; ++r) tree[node].cnt[r] = 0;
            tree[node].cnt[rem] = 1;
            return;
        }
        int mid = start + (end - start) / 2;
        if (start <= idx && idx <= mid) {
            update(2 * node, start, mid, idx, val);
        } else {
            update(2 * node + 1, mid + 1, end, idx, val);
        }
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    Node query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return Node(); // Neutral node
        if (l <= start && end <= r) return tree[node];

        int mid = start + (end - start) / 2;
        if (r <= mid) {
            return query(2 * node, start, mid, l, r);
        }
        if (l > mid) {
            return query(2 * node + 1, mid + 1, end, l, r);
        }

        Node leftRes = query(2 * node, start, mid, l, r);
        Node rightRes = query(2 * node + 1, mid + 1, end, l, r);
        return merge(leftRes, rightRes);
    }

public:
    vector<int> resultArray(vector<int>& nums, int k_val, vector<vector<int>>& queries) {
        k = k_val;
        int n = nums.size();
        tree.resize(4 * n);

        build(1, 0, n - 1, nums);

        vector<int> ans;
        ans.reserve(queries.size());

        for (const auto& q : queries) {
            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            // 1. Persistent update
            update(1, 0, n - 1, index, value);

            // 2. Query range [start, n - 1]
            Node qres = query(1, 0, n - 1, start, n - 1);

            // 3. Extract the count for remainder x
            ans.push_back(qres.cnt[x]);
        }

        return ans;
    }
};