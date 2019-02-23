#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_n 100
#define INF 0x3f3f3f3f
using namespace std;

int dp[max_n + 5][max_n + 5] = {0};
int rmb[max_n + 5] = {0};
int rp[max_n + 5] = {0};
int t[max_n + 5] = {0};

int main()
{
    int n, m, r;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> rmb[i] >> rp[i] >> t[i];
        t[i] = 1000 - t[i];
    }
    cin >> m >> r;
    
    int num = 0;
    for (int i = 0; i < n; i++) {
        for (int j = m; j >= 0; j--) {
            for (int k = r; k >= 0; k--) {
                if (j - rmb[i] >= 0 && k - rp[i] >= 0) {
                    int temp = dp[j][k];
                    dp[j][k] = max(dp[j][k], dp[j - rmb[i]][k - rp[i]] + t[i]);
                    if (j == m && k == r && temp != dp[j][k]) num++;
                }
            }
        }
    }
    cout << 1000 * num - dp[m][r] << endl;
    return 0;
}

