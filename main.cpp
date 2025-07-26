/*
    Programmer : Alexandru Olteanu
    Purpose    : Portfolio simulator with per‑month and per‑year print‑outs.
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ── 1.  Inputs ──────────────────────────────────────────────────────
    cout << "Input initial investment: " << endl;
    double initial;  cin >> initial;

    cout << "Input monthly investment: " << endl;
    double monthly;  cin >> monthly;

    cout << "Do you want to increase monthly investments each X years? 1 for YES, 0 for NO" << endl;
    int want;
    cin >> want;

    int stepYears = -1;
    double raise = -1;
    if (want) {
        cout << "Input years between monthly-investment raises: " << endl;
        cin >> stepYears;
        cout << "How much increase each " << stepYears << " years? : " << endl;
        cin >> raise;
    }

    cout << "Input Expected Profit Percentage / year: " << endl;
    double annualRatePct;  cin >> annualRatePct;

    cout << "Input total years amount: " << endl;
    double totalYears;     cin >> totalYears;

    // ── 2.  Pre‑compute constants ───────────────────────────────────────
    const double monthlyRate = annualRatePct / 100.0 / 12.0;         // r_m
    const int    totalMonths = static_cast<int>(std::round(totalYears * 12));
    const int    stepMonths  = stepYears == -1 ? -1 : stepYears * 12;

    // ── 3.  State variables ─────────────────────────────────────────────
    double balance      = initial;     // portfolio value
    double contribution = monthly;     // current monthly deposit
    double invested     = initial;     // money you actually put in

    cout << fixed << setprecision(2);
    cout << "\n----------------  Timeline  ----------------\n";

    // ── 4.  Main simulation loop (one iteration per month) ──────────────
    for (int m = 0; m < totalMonths; ++m) {
        // deposit, then compound
        balance  += contribution;
        invested += contribution;
        balance  *= 1.0 + monthlyRate;

        // print snapshot after this month
        int year   = m / 12 + 1;       // 1‑based
        int month  = m % 12 + 1;       // 1‑based
        cout << "Year " << setw(2) << year
             << "  Month " << setw(2) << month
             << "  Balance: " << setw(12) << balance
             << "  |  Invested so far: " << invested << '\n';

        // every “step” years, raise future monthly deposits
        if (stepMonths != -1 && (m + 1) % stepMonths == 0)
            contribution += raise;
    }

    // ── 5.  Summary ─────────────────────────────────────────────────────
    cout << "\n--------------  Summary  --------------------\n";
    cout << "Total invested: " << invested << '\n';
    cout << "Portfolio value after " << totalYears
         << " years: " << balance << '\n';

    return 0;
}
