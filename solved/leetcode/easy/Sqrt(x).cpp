class Solution {
public:
    int mySqrt(int x) {
        long long lo = 0, hi = x;
        int ans = 0;
        while(lo <= hi) {
            long long mid = lo + (hi - lo) / 2;
            if (mid * mid <= x) {
                ans = mid;
                lo = mid + 1;
                continue;
            }
            hi = mid - 1;
        }
        return ans;
    }
};