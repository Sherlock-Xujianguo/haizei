#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_n 1500
using namespace std;
int map[max_n + 5][max_n + 5] = {0};
int dp[max_n + 5][max_n + 5] = {0};
int f1[max_n + 5][max_n + 5] = {0};
int f2[max_n + 5][max_n + 5] = {0};


int main()
{
    int n,m;
    cin >> n >> m;
    int rst = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            dp[i][j] = 1;
            cin >> map[i][j];
            f1[i][j] = f2[i][j] = 1;
            if (i > 0 && map[i][j] != map[i - 1][j]) f2[i][j] += f2[i - 1][j];
            if (j > 0 && map[i][j] != map[i][j - 1]) f1[i][j] += f1[i][j - 1];
            if (i == 0 || j == 0) continue;
            else {
                if (map[i][j] != map[i - 1][j - 1]) continue;
                else {
                    dp[i][j] = min(f1[i][j], f2[i][j]);
                    dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + 1);
                    if (dp[i][j] > rst) rst = dp[i][j];
                }
            }
        }
    }

    cout << rst << endl;
    return 0;
}

