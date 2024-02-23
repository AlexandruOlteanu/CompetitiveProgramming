#include<map>
class Solution {
public:
    bool isValid(string s) {
        vector<int> v;
        map<char, int> m;
        m['('] = 1;
        m['['] = 2;
        m['{'] = 3;
        m[')'] = -1;
        m[']'] = -2;
        m['}'] = -3;
        for (auto x : s) {
            int u = m[x];
            if (u > 0) {
                v.push_back(u);
                continue;
            }
            u = -u;
            if (v.empty() || v.back() != u) {
                return false;
            }
            v.pop_back();
        }
        return v.empty();
    }
};