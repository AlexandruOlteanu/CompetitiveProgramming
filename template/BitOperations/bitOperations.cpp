// Bit operations
template<typename T>
bool hasBit(T x, int bit) {
    return ((x >> bit) & 1) != 0;
}

template<typename T>
int countBits(T x) {
    if constexpr (is_same_v<T, int>) {
        return __builtin_popcount(x);
    } else if constexpr (is_same_v<T, long long>) {
        return __builtin_popcountll(x);
    } else {
        static_assert(is_integral_v<T>, "countBits requires an integral type");
        return __builtin_popcountll(static_cast<long long>(x)); // fallback
    }
}

template<typename T>
int highestBit(T x) {
    if (x == 0) return -1;
    if constexpr (is_same_v<T, int>) {
        return 31 - __builtin_clz(x);
    } else if constexpr (is_same_v<T, long long>) {
        return 63 - __builtin_clzll(x);
    } else {
        static_assert(is_integral_v<T>, "highestBit requires an integral type");
        return 63 - __builtin_clzll(static_cast<long long>(x));
    }
}

template<typename T>
int lowestBit(T x) {
    if (x == 0) return -1;
    if constexpr (is_same_v<T, int>) {
        return __builtin_ctz(x);
    } else if constexpr (is_same_v<T, long long>) {
        return __builtin_ctzll(x);
    } else {
        static_assert(is_integral_v<T>, "lowestBit requires an integral type");
        return __builtin_ctzll(static_cast<long long>(x));
    }
}