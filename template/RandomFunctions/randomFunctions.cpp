template <typename T>
long long rangeSum(T a, T b) {
    if (a > b) swap(a, b);
    return 1LL * (b - a + 1) * (a + b) / 2;
}