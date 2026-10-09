class Solution {
public:
    int minInsertions(string s) {
        int insertions = 0;
        int open_count = 0;
        int n = s.length();

        for (int i = 0; i < n; i++) {
            if (s[i] == '(') {
                open_count++;
            } else { // s[i] == ')'
                // Check if next char is also ')'
                if (i + 1 < n && s[i + 1] == ')') {
                    i++; // Skip the second ')'
                } else {
                    insertions++; // Insert one missing ')' to make it '))'
                }

                // Match with an existing '(' or insert a missing '('
                if (open_count > 0) {
                    open_count--;
                } else {
                    insertions++; // Insert a '(' to match this '))'
                }
            }
        }

        // Each remaining unmatched '(' needs '))' (2 insertions)
        insertions += open_count * 2;

        return insertions;
    }
};