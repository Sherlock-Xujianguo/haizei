#include <iostream>
#include <stdio.h>
#include <math.h>
#define max_n 1000000
#define INF 0x3f3f3f3f
using namespace std;

int dp[max_n + 5] = {0};
int sum[max_n + 5] = {0};

int main()
{
    int n, M;
    cin >> n >> M;
    for (int i = 1; i <= n; i++) cin >> sum[i], sum[i] += sum[i - 1];
    for (int i = 1; i <= n; i++) {
        dp[i] = INF;
        for (int j = 0; j < i; j++) {
            dp[i] = min(dp[i], dp[j] + (sum[i] - sum[j])*(sum[i] - sum[j]) + M);
        }
    }
    cout << dp[n] << endl;;
    
    return 0;
}

