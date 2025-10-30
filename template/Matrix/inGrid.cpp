template<typename T>
bool inGrid(T x, T y, T n, T m = -1) {
    if (m == -1) m = n;
    return (x >= 1 && x <= n && y >= 1 && y <= m);
}