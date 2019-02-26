#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <stdlib.h>
#define max_n 100
using namespace std;
struct Rub {
    int t;
    int f;
    int h;
} rub[max_n + 5];

int dp[130];


bool cmp(Rub &a, Rub &b) {
    if(a.t != b.t) return a.t < b.t;
    if (a.f != b.f) return a.f < b.f;
    return a.h < b.h;
}


int main()
{
    int d, g;
    cin >> d >> g;
    for (int i = 1; i <= g; i++) {
        cin >> rub[i].t >> rub[i].f >> rub[i].h;
    }
    sort(rub + 1, rub + g + 1, cmp);
    
    
    dp[0] = 10;
    int ans = -1;
    for (int i = 1; i <= g; i++) {
        for (int j = d; j >= 0; j--){
            if (dp[j] >= rub[i].t) {
                if (j + rub[i].h >= d) {
                    ans == -1 && (ans = rub[i].t);
                }
                dp[j + rub[i].h] = max(dp[j + rub[i].h], dp[j]);
                dp[j] += rub[i].f;
            }
        }
    }
    if (ans == -1) cout << dp[0] << endl;
    else cout << ans << endl;

    return 0;
}
