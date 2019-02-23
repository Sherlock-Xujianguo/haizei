#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stack>
#define max_n 150

using namespace std;

int map[max_n + 5][max_n + 5] = {0};
int f[max_n + 5][max_n + 5] = {0};
int dp[max_n + 5][max_n + 5] = {0};

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char c;
            scanf("%c", &c);
            if (c == 'W') map[i][j] = 1;
            else map[i][j] = 0;
        }
    }

    for (int j = n - 1; j >= 0; j--) {
        int flag = 0;
        for (int i = n - 1; i >= 0; i--) {
            if (map[i][j] == 1) {
                flag++;
                f[i][j] = flag;
            } else {
                flag = 0;
            }
        }
    }

    for (int j = n - 1; j >= 0; j--) {
        stack <int> sta;
        sta.push(n);
        for (int i = n - 1; i >= 0; i--) {
            int k = sta.top();
            dp[i][j] = (i - k) * f[i][j];
            while (f[i][sta.top()] >= f[i][j] && sta.size() != 0) {
                sta.pop();
            }
            sta.push(j);
        }
    }

    printf("%d\n", dp[0][0]);
    return 0;
}

