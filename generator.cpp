#include <bits/stdc++.h>
using namespace std;

std::mt19937 rng {static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count())};

template<typename T>
T rnd(T x) {
    assert(x != 0);
    int sgn = x >= 0 ? 1 : -1;
    if (x < 0) x = -x;
    T result = uniform_int_distribution<T>(0, x - 1)(rng) * sgn;
    return result;
}

template<typename T>
T rnd(T x, T y) {
    if (x > y) swap(x, y);
    T result = uniform_int_distribution<T>(x, y)(rng);
    return result;
}

int main() {

    int numberOfTests = 1;
    // numberOfTests = rnd(1, 10);
    cout << numberOfTests << '\n';

    for (int i = 1; i <= numberOfTests; i++) {
        int x, y;
        x = rnd(1, 1000);
        y = rnd(1, 1000);
        cout << x << " " << y << '\n';
    }
    

    return 0;
}