#include <bits/stdc++.h>
using namespace std;
// Link: https://www.pbinfo.ro/probleme/4245/sumaoni

#define LightningFastReadWrite ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
using ll = long long;

ifstream fin("sumaoni.in");
ofstream fout("sumaoni.out");
#define cin fin
#define cout fout

const long long infbig = numeric_limits<long long> :: max();
const int inf = numeric_limits<int> :: max();
const int MAXN = 2e5 + 5;

void solve(int n) {
    int x = 0;
    for (int i = 1; i <= n; ++i) {
        if (i * (i + 1) / 2 >= n) {
            x = i;
            break;
        }
    }

    if (x * (x + 1) / 2 == n) {
        cout << x << '\n';
        return;
    }

    int have = x * (x + 1) / 2;
    while (have % 2 != n % 2) {
        ++x;
        have = x * (x + 1) / 2;
    }

    int del = have - n;
    cout << x << '\n';
    for (int i = x; i >= 1; --i) {
        if (del >= 2 * i) {
            cout << i << '\n';
            del -= 2 * i;
        }
    }
    assert(del == 0);
}

int main() {

    LightningFastReadWrite

    int n;
    cin >> n;
    solve(n);



    return 0;
}
