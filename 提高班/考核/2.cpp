#include <iostream>
#include <stdio.h>
#define max_n 10000
using namespace std;
int dp[max_n + 5] = {0};
int v[25] = {0};
int m, n;

int main()
{
    cin >> m >> n;
    for (int i = 1; i <= m; i++) {
        cin >> v[i];
    }
    dp[0] = 1;
    for (int i = 1; i <= m; i++) {
        for (int j = n; j >= 1; j--) {
            for (int k = 1; j - k * v[i] >= 0; k++)
                dp[j] += dp[j - k * v[i]];
                dp[j] %= 9973;
        }
    }
    cout << dp[n] << endl;
    return 0;
}

