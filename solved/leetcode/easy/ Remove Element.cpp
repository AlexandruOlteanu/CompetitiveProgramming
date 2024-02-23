class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        vector<int> u;
        for (auto x : nums) {
            if (x == val) continue;
            u.push_back(x);
        }
        nums = u;
        return u.size();
    }
};