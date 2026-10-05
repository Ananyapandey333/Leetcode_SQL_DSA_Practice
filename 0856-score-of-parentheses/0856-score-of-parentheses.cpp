#include <stack>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int scoreOfParentheses(string s) {
        stack<int> st;
        st.push(0);
        
        for (char c : s) {
            if (c == '(') {
                st.push(0); 
            } else {
                int inner = st.top();
                st.pop();
                int val = max(2 * inner, 1);
                
                st.top() += val;
            }
        }
        return st.top();
    }
};