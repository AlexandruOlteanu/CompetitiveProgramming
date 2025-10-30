long long binPow(long long a, long long b) {
    assert(b >= 0);
    long long res = 1;
    for (; b > 0; b >>= 1) {
        if (b & 1) res = res * a;
        a *= a;
    }
    return res;
}