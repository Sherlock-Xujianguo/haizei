/*************************************************************************
	> File Name: solve.cpp
	> Author: hug
	> Mail:   hug@haizeix.com
	> Created Time: Tue Dec 11 14:33:12 2018
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>
using namespace std;
#define MAX_N 10000
#define MAX_M 20
#define MOD_NUM 9973

int dp[MAX_N + 5] = {0};
int w[MAX_M + 5] = {0};

int main() {
    int m, n;
    cin >> m >> n;
    for (int i = 0; i < m; i++) cin >> w[i];
    dp[0] = 1;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j <= n - w[i]; j++) {
            dp[j + w[i]] += dp[j];
            dp[j + w[i]] %= MOD_NUM;
        }
    }
    cout << dp[n] << endl;
    return 0;
}
