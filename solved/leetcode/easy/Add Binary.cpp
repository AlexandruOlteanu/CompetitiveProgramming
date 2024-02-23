class Solution {
public:
    string addBinary(string a, string b) {
        string res = "";
        int r = 0;
        while (!a.empty() || !b.empty()) {
            int x = r;
            if (a.empty()) {
                x += b.back() == '1';
            } else if (b.empty()) {
                x += a.back() == '1';
            } else {
                x += (a.back() == '1') + (b.back() == '1');
            }
            res = char(x % 2 + '0') + res;
            r = x / 2;
            if (!a.empty())a.pop_back();
            if (!b.empty())b.pop_back();
        }

        while (r) {
            if (r > 1) res = "0" + res, r -= 2;
            else res = "1" + res, --r;
        }
        return res;
    }
};