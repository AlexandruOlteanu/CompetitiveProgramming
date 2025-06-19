/*
* Fenwick Tree (Binary Indexed Tree) Template
 *
 * Supports:
 *  - Point updates:     O(log n)
 *  - Prefix sums:       O(log n)
 *  - Range sums [l..r]: O(log n)
 *
 * Usage:
 *  FenwickTree<ll> ft(n);        // Create tree with indices 1 to n
 *  ft.modify(x, delta);          // Add 'delta' to index x
 *  ft.calc(x);                   // Prefix sum from 1 to x
 *  ft.get(l, r);                 // Range sum from l to r (inclusive)
 *  ft.reset();                   // Reset all values to 0
 *  ft.reset(new_n);             // Resize tree to support 1..new_n
 *
 * Notes:
 *  - 1-based indexing
 *  - Generic type: supports int, long long, double, etc.
 *  - Fast and simple alternative to segment trees for sum queries
 *
 * Example:
 *  FenwickTree<ll> ft(10);
 *  ft.modify(3, 5);     // add 5 at index 3
 *  ft.modify(7, 2);     // add 2 at index 7
 *  ft.get(3, 7);        // sum of [3..7] = 5 + ... + 2
 *
 */

// https://github.com/AlexandruOlteanu/CompetitiveProgramming/blob/main/template/Fenwick%20Tree/FenwickTree.cpp
template<typename A>
struct FenwickTree {
    vector<A> array;
    int n;

    FenwickTree(int length) {
        reset(length);
    }

    void modify(int x, ll val) {
        for (; x <= n; x += x & -x) {
            array[x] += val;
        }
    }

    ll calc(int x) {
        ll val = 0;
        for (; x > 0; x -= x & -x) {
            val += array[x];
        }
        return val;
    }

    ll get(int l, int r) {
        if (l > r) return 0;
        return calc(r) - calc(l - 1);
    }

    void reset() {
        fill(array.begin(), array.end(), 0);
    }

    void reset(int new_n) {
        n = new_n;
        array.assign(n + 1, 0);
    }
};
