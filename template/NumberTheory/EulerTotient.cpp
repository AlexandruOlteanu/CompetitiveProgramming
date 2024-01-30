// Algorithm for 1 number

int phi(int n) {
    int res = n;
    int d = 2;
    while (n != 1) {
        if (n % d == 0) {
            while (n % d == 0) n /= d;
            res -= res / d;
        }
        if (d == 2) d = 3;
        else d += 2;
        if (d * d > n) d = n;
    }

    return res;
}


// Algorithm for all numbers from 1 to n

vector<int> phi;
void phiBuild(int n) {
    phi.resize(n + 1);
    for (int i = 0; i <= n; ++i) {
        phi[i] = i;
    }
    for (int i = 2; i <= n; ++i) {
        if (phi[i] == i) {
            for (int j = i; j <= n; j += i) {
                phi[j] -= phi[j] / i;
            }
        }
    }
}