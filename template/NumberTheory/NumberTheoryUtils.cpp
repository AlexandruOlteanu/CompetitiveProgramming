
// https://github.com/AlexandruOlteanu/CompetitiveProgramming/blob/main/template/NumberTheory/NumberTheoryUtils.cpp
struct NumberTheoryUtils {
    int maxn;
    vector<int> mu;
    vector<bool> is_prime;
    vector<int> freq, cnt;

    // Constructor: precalculate up to maxn
    NumberTheoryUtils(int n) : maxn(n), mu(n + 1, 1), is_prime(n + 1, true), freq(n + 1, 0), cnt(n + 1, 0) {
        compute_mobius();
    }

    // Möbius Sieve
    void compute_mobius() {
        mu[0] = 0;
        for (int i = 2; i <= maxn; ++i) {
            if (is_prime[i]) {
                for (int j = i; j <= maxn; j += i) {
                    mu[j] *= -1;
                    is_prime[j] = false;
                }
                for (long long j = 1LL * i * i; j <= maxn; j += 1LL * i * i) {
                    mu[j] = 0;
                }
            }
        }
        is_prime[2] = true;
    }

    // Get Möbius value μ(n)
    int get_mu(int n) const {
        return mu[n];
    };

    // Count pairs (i, j) with GCD(a_i, a_j) == k
    long long count_pairs_with_gcd_k(const vector<int>& a, int k) {
        fill(freq.begin(), freq.end(), 0);
        fill(cnt.begin(), cnt.end(), 0);

        // Normalize array: only use elements divisible by k
        for (int x : a) {
            if (x % k == 0) {
                freq[x / k]++;
            }
        }

        int limit = maxn / k;

        // cnt[d] = how many values divisible by d
        for (int i = 1; i <= limit; ++i) {
            for (int j = i; j <= limit; j += i) {
                cnt[i] += freq[j];
            }
        }

        // Inclusion-Exclusion using Möbius
        long long total = 0;
        for (int d = 1; d <= limit; ++d) {
            long long c = cnt[d];
            if (c >= 2) {
                total += 1LL * mu[d] * c * (c - 1) / 2;
            }
        }

        return total;
    }
};