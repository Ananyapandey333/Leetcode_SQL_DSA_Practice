#include <vector>
#include <unordered_map>

class Solution {
public:
    int totalNumbers(std::vector<int>& digits) {
        std::unordered_map<int, int> count;
        for (int d : digits) {
            count[d]++;
        }

        int validCount = 0;

        // Iterate through all candidate 3-digit even numbers
        for (int num = 100; num <= 998; num += 2) {
            int d1 = num / 100;        // Hundreds digit
            int d2 = (num / 10) % 10;  // Tens digit
            int d3 = num % 10;         // Units digit

            std::unordered_map<int, int> req;
            req[d1]++;
            req[d2]++;
            req[d3]++;

            // Verify if digits are available
            if (count[d1] >= req[d1] && 
                count[d2] >= req[d2] && 
                count[d3] >= req[d3]) {
                validCount++;
            }
        }

        return validCount;
    }
};