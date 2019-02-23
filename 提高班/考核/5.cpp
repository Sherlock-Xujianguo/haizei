#include <iostream>
#include <stdio.h>
#define max_n 100000
using namespace std;
int dp[35][max_n + 5] = {0};

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= max_n; i++) dp[1][i] = i;
    for (int i = 1; i <= n; i++) dp[i][1] = 1;

    for (int i = 2; i <= n; i++) {
        for (int j = 2; j <= max_n; j++) {
            dp[i][j] = dp[i - 1][j - 1] + dp[i][j - 1] + 1;
            if (i == n && dp[i][j] >= m) {
                cout << j << endl;
                break;
            }
        }
    }
    return 0;
}

