#include <vector>
#include <string>

class Solution {
public:
    std::vector<std::string> generateParenthesis(int n) {
        std::vector<std::string> result;
        std::string current = "";
        backtrack(result, current, 0, 0, n);
        return result;
    }

private:
    void backtrack(std::vector<std::string>& result, std::string& current, int open, int close, int max) {
        if (current.length() == max * 2) {
            result.push_back(current);
            return;
        }

        if (open < max) {
            current.push_back('(');
            backtrack(result, current, open + 1, close, max);
            current.pop_back(); // Backtrack
        }
        
        if (close < open) {
            current.push_back(')');
            backtrack(result, current, open, close + 1, max);
            current.pop_back(); // Backtrack
        }
    }
};