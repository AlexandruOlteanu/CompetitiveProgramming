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

    int n , k , l = 0 , kk = 0 , v[100005] , kkmax=0; 
    cin >> n >> k ;
    for (int i = 1 ; i <= n ; i ++){
         cin >> v[i];
    }
    
    for(int i = 1 ; i < n ; i ++){
         kk=0;
         for(int j = i + 1 ; j <= n ; j ++){
             if (v[i] != v[j]){
                 ++kk;
                 if(kk >= k){
                     l++;
                 }
             }else{
                kk=0;
             }
         }
    }


    return 0;
}
