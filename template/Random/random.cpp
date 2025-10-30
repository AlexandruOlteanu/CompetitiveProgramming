std::mt19937 rng {
    static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count())
};
template<typename T>
T rnd(T x) {
    assert(x != 0);
    int sgn = x >= 0 ? 1 : -1;
    if (x < 0) x = -x;
    T result = uniform_int_distribution<T>(0, x - 1)(private_helpers::rng) * sgn;
    return result;
}

template<typename T>
T rnd(T x, T y) {
    if (x > y) swap(x, y);
    T result = uniform_int_distribution<T>(x, y)(private_helpers::rng);
    return result;
}