class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int ans = -1;
        int lo = 0, hi = nums.size() - 1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (nums[mid] <= target) {
                ans = mid;
                lo = mid + 1;
                continue;
            }
            hi = mid - 1;
        } 
        if (ans == -1) return 0;
        if (nums[ans] != target) ++ans;
        return ans;
    }
};