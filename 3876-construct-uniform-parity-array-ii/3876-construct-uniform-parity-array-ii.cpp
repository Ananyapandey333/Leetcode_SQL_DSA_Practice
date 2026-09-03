class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        long long minOdd = LLONG_MAX, minEven = LLONG_MAX;
        bool hasOdd = false, hasEven = false;
        
        for (int x : nums1) {
            if (x % 2 == 1) {
                hasOdd = true;
                minOdd = min(minOdd, (long long)x);
            } else {
                hasEven = true;
                minEven = min(minEven, (long long)x);
            }
        }
        
        // Target: all odd. Every even needs a smaller odd to exist.
        bool targetOdd = (!hasEven) || (hasOdd && minOdd < minEven);
        
        // Target: all even. Every odd needs a smaller odd (impossible for the
        // minimum odd) -> only works if there are no odd elements at all.
        bool targetEven = !hasOdd;
        
        return targetOdd || targetEven;
    }
};