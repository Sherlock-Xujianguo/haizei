#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
#define max_n 350
#define max_m 120

int val[max_n + 5] = {0};
int c[5] = {0};
int dp[max_m + 5][max_m + 5][max_m + 5][max_m + 5] = {0};

int main()
{
    int n, m, b;
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> val[i];
    for (int i = 0; i < m; i++) {
        cin >> b;
        c[b]++;
    }
    for (int i = 0; i <= c[1]; i++) {
        for (int j = 0; j <= c[2]; j++) {
            for (int k = 0; k <= c[3]; k++) {
                for (int l = 0; l <= c[4]; l++) {
                    int index = i + 2 * j + 3 * k + 4 * l, temp = 0;
                    if(i) temp = max(temp, dp[i - 1][j][k][l]);
                    if(j) temp = max(temp, dp[i][j - 1][k][l]);
                    if(k) temp = max(temp, dp[i][j][k - 1][l]);
                    if(l) temp = max(temp, dp[i][j][k][l - 1]);
                    dp[i][j][k][l] = temp + val[index];
                }
            }
        }
    }
    cout << dp[c[1]][c[2]][c[3]][c[4]] << endl;
    return 0;
}

