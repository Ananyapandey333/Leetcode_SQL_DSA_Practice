class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        for(int i = 0; i < nums1.size() ; i++){
            if(nums1[i] % 2 == 0){
                return true;
            }
            else if(nums1[i] % 2 != 0){
                return true;
            }
        }  
        return true;  
    }
};