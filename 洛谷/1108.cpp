#include <iostream>
#include <stdio.h>
#define max_n 5000
using namespace std;

int dp[max_n + 5] = {0};
int f[max_n + 5] = {0};
int value[max_n + 5] = {0};


int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> value[i];
    f[0] = 1;
    dp[0] = 1;
    int max_dp = 1;
    int max_f = 0;
    for (int i = 1; i < n; i++) {
        dp[i] = 1;
        for (int j = 0; j < i; j++) {
            if (value[i] < value[j]) {
                dp[i] = max(dp[i], dp[j] + 1);
                if (dp[i] > max_dp) max_dp = dp[i];
            }
        }
    }
    for (int i = 1; i < n; i++) {
        for (int j = i - 1; j >= 0; j--) {
            if (dp[i] == dp[j] && value[i] == value[j]) f[j] = 0;
            if (dp[i] - dp[j] == 1 && value[i] < value[j]) f[i] += f[j];
        }
        if (f[i] == 0) f[i] = 1;
    }
    for (int i = 0; i < n; i++) {
        if (dp[i] == max_dp) max_f += f[i];
    }
    cout << max_dp << " " << max_f << endl;
    
    return 0;
}

