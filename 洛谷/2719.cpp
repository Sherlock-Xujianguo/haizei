#include <iostream>
#include <stdio.h>
#define max_n 1250
using namespace std;

float dp[max_n + 5][max_n + 5] = {0};

int main()
{
    int n;
    cin >> n;
    n>>=1;
    for (int i = 2; i <= n; i++) {
        dp[i][0] = dp[0][i] = 1;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dp[i][j] = (dp[i-1][j] + dp[i][j-1]) * 0.5;
        }
    }
    printf("%.4f\n", dp[n][n]);
    
    return 0;
}

