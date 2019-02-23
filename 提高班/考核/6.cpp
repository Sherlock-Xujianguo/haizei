#include <iostream>
#include <stdio.h>
#include <stack>
#define max_n 1000
using namespace std;

int f[max_n + 5][max_n + 5] = {0};
int dp[max_n + 5][max_n + 5] = {0};
int n, m;

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> f[i][j];
        }
    }

    for (int i = n - 2; i >= 0; i--) {
        for (int j = 0; j < m; j++) {
            if (f[i][j] == 0) continue;
            f[i][j] += f[i+1][j];
        }
    }
    
    int ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        stack <int> sta;
        dp[i][m] = 0;
        sta.push(m);
        for (int j = m - 1; j >= 0; j--) {
            if (f[i][j] == 0) {
                dp[i][j] = 0;
                sta.push(j);
                continue;
            }
            int k;
            while (f[i][sta.top()] >= f[i][j]) sta.pop();
            k = sta.top();
            dp[i][j] = ((k - j) * f[i][j] + dp[i][k]) % 100007;
            sta.push(j);
            ans += dp[i][j];
            ans %= 100007;
        }
    }
    cout << ans <<endl;
    return 0;
}

