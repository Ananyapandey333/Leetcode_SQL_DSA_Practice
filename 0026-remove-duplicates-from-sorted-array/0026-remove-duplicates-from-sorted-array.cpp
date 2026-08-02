class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        vector<int>arr;
        for(int i = 0; i<nums.size()-1;i++){
            if(
            nums[i]!=nums[i+1]){
                arr.push_back(nums[i]);
            }
        }
        arr.push_back(nums.back());
        for(int i = 0; i < arr.size();i++){
            nums[i]=arr[i];
        }
        return arr.size();
        
    }
};