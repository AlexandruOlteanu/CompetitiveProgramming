long long rBinPow(long long a, long long b, long long m = -1) {
    assert(b >= 0);
    if (m == -1) m = mod;
    long long  res = 1; a %= m;
    for (; b > 0; b >>= 1) {
        if (b & 1) res = res * a % m;
        a = a * a % m;
    }
    return res;
}