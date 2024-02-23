class Solution {
public:
    int lengthOfLastWord(string s) {
        int ans = 0;
        int sz = s.size();
        int i = 0;
        while (i < sz) {
            while (i < sz && s[i] == ' ')++i;
            if (i == sz) break;
            int j = i;
            while (j < sz && s[j] != ' ')++j;
            ans = j - i;
            i = j;
        }
        return ans;
    }
};