#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define max_n 100
using namespace std;
int dp[max_n + 5][max_n + 5] = {0};
int x[max_n + 5] = {0};

int f(int i, int j) {
    return (abs(x[i] - x[j]) * (j - i + 1));
}

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
    }

    for (int i = 1; i <= n; i++) dp[i][i] = x[i];
    for (int l = 1; l < n; l++) {
        for (int i = 1; i + l <= n; i++ ) {
            int j = i + l;
            for (int k = i ; k < j; k++) {
                dp[i][j] = max(dp[i][j], dp[i][k] + dp[k + 1][j]);
            }
            dp[i][j] = max(dp[i][j], f(i, j));
        
        }
    }
    cout << dp[1][n] << endl;
    
    return 0;
}

