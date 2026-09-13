#include <vector>
#include <unordered_map>
#include <algorithm>

class Solution {
public:
    int largestOverlap(std::vector<std::vector<int>>& img1, std::vector<std::vector<int>>& img2) {
        int n = img1.size();
        
        std::vector<std::pair<int, int>> ones1;
        std::vector<std::pair<int, int>> ones2;
        
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                if (img1[r][c] == 1) ones1.push_back({r, c});
                if (img2[r][c] == 1) ones2.push_back({r, c});
            }
        }
        
        // Map encoded shift vector to frequency
        std::unordered_map<int, int> shiftCounts;
        int maxOverlap = 0;
        
        for (const auto& p1 : ones1) {
            for (const auto& p2 : ones2) {
                int rowShift = p1.first - p2.first;
                int colShift = p1.second - p2.second;
                
                // Encode (rowShift, colShift) into a unique integer key
                // Since shifts range from -(n-1) to (n-1), adding 100 ensures unique positive keys
                int key = (rowShift + 100) * 1000 + (colShift + 100);
                
                maxOverlap = std::max(maxOverlap, ++shiftCounts[key]);
            }
        }
        
        return maxOverlap;
    }
};