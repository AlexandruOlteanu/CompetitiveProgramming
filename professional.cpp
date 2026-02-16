/* =====================================================================================================

     ██████╗ ██╗   ██╗ ███╗  ██╗      ██╗ ███████╗  █████╗  ████████╗  █████╗  ██████╗ 
    ██╔════╝ ╚██╗ ██╔╝ ████╗ ██║      ██║ ██╔════╝ ██╔══██╗ ╚══██╔══╝ ██╔══██╗ ██╔══██╗
    ╚█████╗   ╚████╔╝  ██╔██╗██║      ██║ █████╗   ██║  ╚═╝    ██║    ██║  ██║ ██████╔╝
     ╚═══██╗   ╚██╔╝   ██║╚████║ ██╗  ██║ ██╔══╝   ██║  ██╗    ██║    ██║  ██║ ██╔══██╗
    ██████╔╝    ██║    ██║ ╚███║ ╚█████╔╝ ███████╗ ╚█████╔╝    ██║    ╚█████╔╝ ██║  ██║
    ╚═════╝     ╚═╝    ╚═╝  ╚══╝  ╚════╝  ╚══════╝  ╚════╝     ╚═╝     ╚════╝  ╚═╝  ╚═╝

    Injected:
    ->   13  Official Championships Problems
    ->   0   Hard Problems (Aimed to improve my skills and deep thinking)
    ->   4   Leveling Up Problems (A mix of speed and thinking, climbing the Level AK ladder)
    ->   0   Virtual Contests Problems (Aimed to simulate live performances)
    ->   10  Random Problems from different sites
   ===================================================================================================== */

#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1000000007;
// constexpr int mod = 998244353;

/* =====================================================================================================
   -> Read from file
   ===================================================================================================== */
// ifstream fin("input.in");
// ofstream fout("output.out");
// #define cin fin
// #define cout fout

/* =====================================================================================================
   -> Debugging, Timings & Tests Generator
   ===================================================================================================== */
// #define ActivateDebug
// #define ActivateTimings
// #define TestsGenerator
namespace External {

    #if defined(ActivateDebug) && !defined(TestsGenerator)
        // Code: https://github.com/AlexandruOlteanu/CompetitiveProgramming/tree/main/external/debug.hpp
        #include "external/debug.hpp"
        #define dbg(...)   DebugUtil::dbgImpl  (__LINE__, #__VA_ARGS__, __VA_ARGS__)
        #define dbgR(...)  DebugUtil::dbgRImpl (__LINE__, #__VA_ARGS__, __VA_ARGS__)
        #define Sdbg(...)  DebugUtil::SdbgImpl (__LINE__, #__VA_ARGS__, __VA_ARGS__)
        #define SdbgR(...) DebugUtil::SdbgRImpl(__LINE__, #__VA_ARGS__, __VA_ARGS__)
    #else
        void dbg(...) {} void dbgR(...) {}string Sdbg(...)  { return ""; } string SdbgR(...) { return ""; }
    #endif

    #if defined(ActivateTimings) && !defined(TestsGenerator)
        // Code: https://github.com/AlexandruOlteanu/CompetitiveProgramming/tree/main/external/timings.hpp
        #include "external/timings.hpp"
    #else
        void reset() {} void startInitializationTimer() {}
        void endInitializationTimerAndStartExecutionTimer() {}
        void endExecutionTimer() {} void debugTimings() {}
    #endif
}
using namespace External;

namespace Functions {
    void ActivateFastIO() { ios_base::sync_with_stdio(false); cin.tie(nullptr); }
    void ActivateHighDoublePrecision() { cout << fixed << setprecision(17); }
    void YES() { cout << "YES\n"; }  void Yes() { cout << "Yes\n"; }  void yes() { cout << "yes\n"; }
    void NO () { cout << "NO\n"; }  void No () { cout << "No\n"; }  void no () { cout << "no\n"; }
    void NoSolution() {cout << "-1\n";}
}
using namespace Functions;

/* =====================================================================================================
   -> Defines
   ===================================================================================================== */
namespace Define {
    #define all(x) (x).begin(), (x).end()
    #define all1(x) ++(x).begin(), (x).end()
    #define rall(x) (x).rbegin(), (x).rend()
    #define rall1(x) (x).rbegin(), --(x).rend()
    #define fi first
    #define se second
    #define pb push_back
    using ll  = long long;
    using pii = pair<int, int>;
    constexpr pair<int, int> dir4[] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
    constexpr pair<int, int> dir8[] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    constexpr pair<int, int> dirDiag[] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    constexpr long long infBig = numeric_limits<long long> :: max() - 24;
    constexpr long long infMid = 1e15;
    constexpr int inf = numeric_limits<int> :: max() - 24;
    constexpr int infSmall = 1e9;
}
using namespace Define;

/* =====================================================================================================
   -> Templates written before
   -> Full Code: https://github.com/AlexandruOlteanu/CompetitiveProgramming/tree/main/template
   ===================================================================================================== */
namespace Template {}
using namespace Template;

constexpr int MAXN = 2e5 + 2;



void Initialize() {}

void Inject(const int testNr, const bool onLastTest) {
    dbg(testNr);
    if (onLastTest) {}

    
}

constexpr bool activateMultipleTests = true;
int main() {

    ActivateFastIO();
    ActivateHighDoublePrecision();

    int numberOfTests = 1;
    if (activateMultipleTests) {
        cin >> numberOfTests;
    }

    startInitializationTimer();

    Initialize();

    endInitializationTimerAndStartExecutionTimer();

    for (int testNr = 1; testNr <= numberOfTests; ++testNr) {
        // cout << "Case #" << testNr << ": ";
        // cout << "Test #" << testNr << ": ";
        Inject(testNr, testNr == numberOfTests);
    }

    endExecutionTimer();
    debugTimings();

    return 0;
}