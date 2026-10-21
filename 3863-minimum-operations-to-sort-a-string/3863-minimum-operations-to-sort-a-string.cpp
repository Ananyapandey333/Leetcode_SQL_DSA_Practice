#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minOperations(string s) {
        int n = s.length();
        
        // Case 0: Already sorted
        if (is_sorted(s.begin(), s.end())) {
            return 0;
        }
        
        // Cannot sort string of length <= 2 if it's not already sorted
        if (n <= 2) {
            return -1;
        }
        
        // Case 1: Try sorting prefix s[0 ... n-2]
        string t1 = s;
        sort(t1.begin(), t1.end() - 1);
        if (is_sorted(t1.begin(), t1.end())) {
            return 1;
        }
        
        // Try sorting suffix s[1 ... n-1]
        string t2 = s;
        sort(t2.begin() + 1, t2.end());
        if (is_sorted(t2.begin(), t2.end())) {
            return 1;
        }
        
        // Find absolute min and max characters
        char min_char = *min_element(s.begin(), s.end());
        char max_char = *max_element(s.begin(), s.end());
        
        // Case 3: Requires 3 operations ONLY if the ONLY min_char is at index n-1 
        // AND the ONLY max_char is at index 0.
        // (i.e. s[0] == max_char, s[n-1] == min_char, and neither min_char nor max_char appear anywhere in s[1 ... n-2])
        if (s[0] == max_char && s[n - 1] == min_char) {
            bool min_in_middle = false;
            bool max_in_middle = false;
            for (int i = 1; i < n - 1; ++i) {
                if (s[i] == min_char) min_in_middle = true;
                if (s[i] == max_char) max_in_middle = true;
            }
            if (!min_in_middle && !max_in_middle) {
                return 3;
            }
        }
        
        // Case 2: 2 operations suffice for all other cases
        return 2;
    }
};