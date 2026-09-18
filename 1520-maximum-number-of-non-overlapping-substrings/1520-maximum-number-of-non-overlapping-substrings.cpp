#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {
        int n = s.length();
        vector<int> L(26, n), R(26, -1);

        // Step 1: Find the first and last occurrence of each character
        for (int i = 0; i < n; ++i) {
            int c = s[i] - 'a';
            L[c] = min(L[c], i);
            R[c] = max(R[c], i);
        }

        vector<pair<int, int>> validIntervals;

        // Step 2: Expand intervals for each character
        for (int i = 0; i < 26; ++i) {
            if (L[i] == n) continue; // Character not present

            int left = L[i];
            int right = R[i];
            bool isValid = true;

            for (int j = left; j <= right; ++j) {
                int c = s[j] - 'a';
                if (L[c] < left) {
                    isValid = false; // Overlaps with an earlier character's start
                    break;
                }
                right = max(right, R[c]);
            }

            if (isValid) {
                validIntervals.push_back({left, right});
            }
        }

        // Step 3: Sort valid intervals by their end index
        sort(validIntervals.begin(), validIntervals.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.second < b.second;
        });

        // Step 4: Greedy selection of non-overlapping intervals
        vector<string> result;
        int prevEnd = -1;

        for (const auto& interval : validIntervals) {
            int start = interval.first;
            int end = interval.second;

            if (start > prevEnd) {
                result.push_back(s.substr(start, end - start + 1));
                prevEnd = end;
            }
        }

        return result;
    }
};