#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>
using namespace std;
#define MAX_N 100
#define MAX_V 100000
int dp[MAX_N + 5][MAX_V + 5] = {0};
int v[MAX_N + 5], w[MAX_N + 4], s[MAX_N + 5] = {0};
struct Data {
    int val, j;
} q[MAX_V + 5];
int head, tail;

int main() {
    int n, V;
    cin >> V >> n;
    for (int i = 1; i <= n; i++) cin >> v[i] >> w[i] >> s[i];
    for (int i = 1; i <= n; i++) {
        for (int r = 0; r < v[i]; r++) {
            head = 0, tail = 0;
            q[tail++] = {dp[i - 1][r], r};
            dp[i][r] = dp[i - 1][r];
            for (int j = r + v[i]; j <= V; j += v[i]) {
                int val = dp[i - 1][j] - j / v[i] * w[i];
                while (head < tail && val >= q[tail - 1].val) --tail;
                q[tail++] = {val, j};
                if ((j - q[head].j) / v[i] > s[i]) ++head;
                dp[i][j] = q[head].val + j / v[i] * w[i];
            }
        }
    }
    cout << dp[n][V] << endl;
    return 0;
}