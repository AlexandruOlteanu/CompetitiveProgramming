// Returns a vector where pi[i] = Longest prefix in [0..i] that
// it's also a suffix in [0..i]
template <typename T>
std::vector<int> buildFailureFunction(const T& pattern) {
    int m = pattern.size();
    std::vector<int> pi(m, 0);
    int length = 0;

    for (int i = 1; i < m; ++i) {
        while (length > 0 && pattern[i] != pattern[length]) {
            length = pi[length - 1];
        }

        if (pattern[i] == pattern[length]) {
            length++;
            pi[i] = length;
        } else {
            pi[i] = 0;
        }
    }

    return pi;
}