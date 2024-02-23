class Solution {
public:

    int minimumOneBitOperations(int n) {
        int sum = 0;
        int last = 1;
        for (int i = 30; i >= 0; --i) {
            if ((n & (1 << i)) > 0) {
                if (last < 0) {
                    sum -= (1LL << (i + 1)) - 1;
                    last = 1;
                    continue;
                }
                sum += (1LL << (i + 1)) - 1;
                last = -1;
            }
        }
        return sum;
}
};

// 0010000
// 0010001
// 0010011
// 0010010
// 0010110
// 0010111
// 0010101
// 0010100
// 0011100

// 100
// 101
// 111
// 110
// 010

// 1000
// 1001
// 1011
// 1010
// 1110
// 1111
// 1101
// 1100
// 0100

// 10
// 11
// 01
// 00

// 7 - 3 = 4
