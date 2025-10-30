template<typename T>
T gcd(T a, T b) {
    return b ? gcd(b, a % b) : a;
}

long long lcm(const long long a, const long long b) {
    return a / gcd(a, b) * b;
}