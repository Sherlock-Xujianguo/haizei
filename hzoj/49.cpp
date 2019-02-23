#include <iostream>
#include <stdio.h>
#define max_n 100000
using namespace std;
int dp[max_n + 5] = {0};
int v[max_n + 5] = {0};
int w[max_n + 5] = {0};
int s[max_n + 5] = {0};
int V, n;
int main()
{
    cin >> V >> n;
    for (int i = 0; i < n; i++) {
        cin >> v[i] >> w[i] >> s[i];
    }
    for (int i = 0; i < n ; i++) {
        for (int j = 1 ; j <= s[i]; j++) {
            for (int k = V; k - v[i] >= 0; k--) {
                dp[k] = max(dp[k], dp[k - v[i]] + w[i]);
            }
        }
    }
    cout << dp[V] << endl;
    return 0;
}
