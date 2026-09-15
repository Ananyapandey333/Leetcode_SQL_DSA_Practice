#include <string>
#include <algorithm>
class Solution {
public:
    int maxPalindromes(std::string s, int k) {
        int n = s.length();
        int count = 0;
        int i = 0;
        while (i < n) {
            // Check for a palindrome of length k ending at or before i
            if (i + k - 1 < n && isPalindrome(s, i, i + k - 1)) {
                count++;
                i += k; // Skip past the found palindrome
            } 
            // Check for a palindrome of length k + 1 ending at or before i
            else if (i + k < n && isPalindrome(s, i, i + k)) {
                count++;
                i += k + 1; // Skip past the found palindrome
            } 
            else {
                i++;
            }
        }

        return count;
    }

private:
    bool isPalindrome(const std::string& s, int left, int right) {
        while (left < right) {
            if (s[left] != s[right]) return false;
            left++;
            right--;
        }
        return true;
    }
};