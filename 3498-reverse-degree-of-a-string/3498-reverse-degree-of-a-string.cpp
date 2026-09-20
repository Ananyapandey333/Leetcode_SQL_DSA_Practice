#include <string>

class Solution {
public:
    int reverseDegree(std::string s) {
        int totalSum = 0;
        
        for (int i = 0; i < s.length(); ++i) {
            // Calculate value in reversed alphabet ('a' -> 26, 'z' -> 1)
            int reversedAlphaVal = 'z' - s[i] + 1;
            
            // 1-based index in the string
            int stringIndex = i + 1;
            
            // Add product to total sum
            totalSum += reversedAlphaVal * stringIndex;
        }
        
        return totalSum;
    }
};