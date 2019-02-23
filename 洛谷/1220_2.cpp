#include <iostream>
#include <stdio.h>
#include <string.h>
#define max_n 50
using namespace std;

int dp[max_n + 5][max_n + 5][2];
int p[max_n + 5] = {0};
int sum[max_n + 5] = {0};
int n, c;

int W(int i, int j, int n) {
    return sum[n] - sum[j] + sum[i - 1];
}

int main()
{
    cin >> n >> c;
    for (int i = 1; i <= n; i++) {
        cin >> p[i] >> sum[i];
        sum[i] += sum[i - 1];
    }
    memset(dp, 0x3f, sizeof(dp));
    dp[c][c][0] = dp[c][c][1] = 0;
    for (int i = c; i >= 1; i--) {
        for (int j = i + 1; j <= n; j++) {
            dp[i][j][0] = min(dp[i+1][j][0] + W(i+1, j, n) * (p[i+1] - p[i]), \
                              dp[i+1][j][1] + W(i+1, j, n) * (p[j] - p[i]));
            dp[i][j][1] = min(dp[i][j-1][0] + W(i, j-1, n) * (p[j] - p[i]), \
                              dp[i][j-1][1] + W(i, j-1, n) * (p[j] - p[j-1]));
        }
    }
    cout << min(dp[1][n][0], dp[1][n][1]) << endl;
    return 0;
}

