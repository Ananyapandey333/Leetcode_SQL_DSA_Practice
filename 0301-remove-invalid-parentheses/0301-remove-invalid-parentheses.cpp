#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_set>
class Solution {
private:
    bool isValid(const std::string& s) {
        int count = 0;
        for (char c : s) {
            if (c == '(') {
                count++;
            } else if (c == ')') {
                count--;
                if (count < 0) return false; // More closing than opening
            }
        }
        return count == 0;
    }

public:
    std::vector<std::string> removeInvalidParentheses(std::string s) {
        std::vector<std::string> result;
        if (s.empty()) return result;

        std::queue<std::string> q;
        std::unordered_set<std::string> visited;

        q.push(s);
        visited.insert(s);

        bool found = false;

        while (!q.empty()) {
            std::string curr = q.front();
            q.pop();

            if (isValid(curr)) {
                result.push_back(curr);
                found = true; // Mark that we found a valid string at the current level
            }

            // If we found valid string(s) at this level, stop generating child states for the next level
            if (found) continue;

            // Generate all possible states by removing one parenthesis at a time
            for (size_t i = 0; i < curr.length(); ++i) {
                // Skip non-parenthesis characters
                if (curr[i] != '(' && curr[i] != ')') continue;

                // Create substring by omitting the character at index i
                std::string next_str = curr.substr(0, i) + curr.substr(i + 1);

                if (visited.find(next_str) == visited.end()) {
                    visited.insert(next_str);
                    q.push(next_str);
                }
            }
        }

        return result;
    }
};