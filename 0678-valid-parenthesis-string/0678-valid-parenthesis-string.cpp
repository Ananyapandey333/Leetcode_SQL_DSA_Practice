class Solution {
public:
    bool checkValidString(string s) {
        int low = 0;   // Minimum count of unmatched '('
        int high = 0;  // Maximum count of unmatched '('

        for (char c : s) {
            if (c == '(') {
                low++;
                high++;
            } else if (c == ')') {
                low--;
                high--;
            } else { // c == '*'
                low--;   // treated as ')'
                high++;  // treated as '('
            }

            // low cannot be less than 0 because we cannot balance 
            // a ')' before a '(' appears
            if (low < 0) {
                low = 0;
            }

            // If high drops below 0, we have too many ')'
            if (high < 0) {
                return false;
            }
        }

        // String is valid if it's possible to have 0 unmatched '('
        return low == 0;
    }
};