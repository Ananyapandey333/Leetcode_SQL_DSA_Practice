#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    string reverseParentheses(string s) {
        vector<char> st;
        
        for (char c : s) {
            if (c == ')') {
                string temp = "";
                // Pop characters until the matching '(' is found
                while (!st.empty() && st.back() != '(') {
                    temp += st.back();
                    st.pop_back();
                }
                // Pop the matching '('
                if (!st.empty()) {
                    st.pop_back();
                }
                // Push the reversed substring back into the stack
                for (char ch : temp) {
                    st.push_back(ch);
                }
            } else {
                st.push_back(c);
            }
        }
        
        return string(st.begin(), st.end());
    }
};