class Solution {
public:
    int count = 0;

    // Helper function returns pair<subtree_sum, node_count>
    pair<int, int> dfs(TreeNode* node) {
        if (!node) return {0, 0};

        auto left = dfs(node->left);
        auto right = dfs(node->right);

        int totalSum = node->val + left.first + right.first;
        int totalCount = 1 + left.second + right.second;

        // Truncated integer division matches the "rounded down" requirement
        if (node->val == totalSum / totalCount) {
            count++;
        }

        return {totalSum, totalCount};
    }

    int averageOfSubtree(TreeNode* root) {
        dfs(root);
        return count;
    }
};