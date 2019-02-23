#include <iostream>
#include <stdio.h>
#define max_n 1000
using namespace std;

int main()
{
    long long dp[max_n + 5] = {0};
    dp[0] = dp[1] = 1;
    int n;
    cin >> n;
    for (int i = 2; i <= n; i++) {
        if (i % 2 == 1) dp[i] = dp[i - 1];
        else dp[i] = dp[i - 1] + dp[i / 2];
    }
    cout << dp[n] << endl;
    return 0;
}

