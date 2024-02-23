class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        set<int> s;
        vector<int> u;
        for (auto x : nums) {
            if (s.count(x)) continue;
            u.push_back(x);
            s.insert(x);
        }
        nums = u;
        return s.size();
    }
};