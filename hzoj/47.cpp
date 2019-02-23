#include <iostream>
#include <stdio.h>
#define max_n 100
#define max_v 10000
using namespace std;
int dp[max_v + 5] =  {0};
int v[max_n + 5] = {0};
int w[max_n + 5] = {0};
int V, n;
int main()
{
    cin >> V >> n;

    for (int i = 0; i < n ; i ++)
        cin >> v[i] >> w[i];
    for (int i = 0; i < n; i++) {
        for (int j = V; j >= v[i]; j--) {
            dp[j] = max(dp[j], dp[j - v[i]] + w[i]);
        }
    }
    cout << dp[V] << endl;
    return 0;
}

