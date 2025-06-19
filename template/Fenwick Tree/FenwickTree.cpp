#include <algorithm>
/*
Template created by Alexandru Olteanu {AlexandruINV}
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
