#include <iostream>
#include <stdio.h>
#define max_n 100
#define max_v 100000
using namespace std;
int dp[max_v + 5] = {0};
int v[max_n + 5], w[max_n + 5], s[max_n + 5];
int n, V;

int main()
{
    cin >> V >> n;
    for (int i = 0; i < n; i++) cin >> v[i] >> w[i] >> s[i];
    for (int i = 0; i < n; i++ ) {
        for (int k = 1; k <= s[i]; k <<= 1) {
            int K = (s[i] - k + 1 < k ? s[i] - k + 1 : k);
            int vv = v[i] * K, ww = w[i] * K;
            for (int j = V; j - vv >= 0; j--) {
                dp[j] = max(dp[j], dp[j - vv] + ww);
            }
        }
    }
    cout << dp[V] << endl;
    return 0;
}

