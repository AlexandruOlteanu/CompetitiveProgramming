// Problem Link : https://leetcode.com/problems/palindrome-number/

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) return false;
        long long o = 0;
        int x1 = x;
        while (x) {
            o = o * 10 + x % 10;
            x /= 10;
        }
        return o == x1;
    }
};
