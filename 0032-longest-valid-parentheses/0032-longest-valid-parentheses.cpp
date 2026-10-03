#include <string>
#include <stack>
#include <algorithm>

class Solution {
public:
    int longestValidParentheses(std::string s) {
        std::stack<int> st;
        st.push(-1); // Base index for valid substring length calculation
        int maxLength = 0;

        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(') {
                st.push(i);
            } else {
                st.pop();
                if (st.empty()) {
                    // Current ')' has no matching '('; reset base index
                    st.push(i);
                } else {
                    // Valid substring length = current index - last unmatched index
                    maxLength = std::max(maxLength, i - st.top());
                }
            }
        }

        return maxLength;
    }
};