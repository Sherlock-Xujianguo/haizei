#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_n 50
using namespace std;

int f[max_n + 5][max_n + 5][2] = {0};
int d[max_n + 5] = {0};
int sum[max_n + 5] = {0};

int n, c;

int main()
{
    cin >> n >> c;
    for (int i = 1; i <= n; i++) {
        cin >> d[i];
        cin >> sum[i];
        sum[i] += sum[i - 1];
    }
    memset(f, 127, sizeof(f));
    f[c][c][0] = f[c][c][1] = 0;
    for (int j = c; j <= n; j++) {
        for (int i = j - 1; i >= 1; i--) {
            
            f[i][j][0] = min(f[i + 1][j][0] + \
                             (d[i + 1] - d[i]) * (sum[i] + sum[n] - sum[j]), \
                             f[i + 1][j][1] + \
                             (d[j] - d[i]) * (sum[i] + sum[n] - sum[j]));
            
            f[i][j][1] = min(f[i][j - 1][1] + \
                             (d[j] - d[j - 1]) * (sum[i - 1] + sum[n] - sum[j - 1]), \
                             f[i][j - 1][0] + \
                             (d[j] - d[i]) * (sum[i - 1] + sum[n] - sum[j - 1]));
         }
    }
    cout << min(f[1][n][0], f[1][n][1]) << endl;
    return 0;
}
