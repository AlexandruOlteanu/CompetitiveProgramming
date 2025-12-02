#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void FastIO() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
}

void HighPrecisionOutput() {
    cout << fixed << setprecision(17);
}

// ifstream fin("input.in");
// ofstream fout("output.out");
// #define cin fin
// #define cout fout

const long long infbig = numeric_limits<long long> :: max();
const int inf = numeric_limits<int> :: max();
const int MAXN = 2e5 + 5;



int main() {

    FastIO();
    HighPrecisionOutput();

    int a;
    long long b;
    cin >> a >> b;
    cout << a + b << '\n';
    
    cin >> a >> b;
    cout << a - b << '\n';


    return 0;
}
