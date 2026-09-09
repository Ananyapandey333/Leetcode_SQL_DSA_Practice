class Solution {
public:
    long long countCommas(long long n) {
        long long total = 0;
        long long threshold = 1000;

        while (n >= threshold) {
            total += (n - threshold + 1);
            
            // Prevent 64-bit integer overflow when multiplying by 1000
            if (threshold > LLONG_MAX / 1000) {
                break;
            }
            threshold *= 1000;
        }

        return total;
    }
};