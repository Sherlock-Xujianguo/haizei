#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>

#define max_n 1000000
using namespace std;

typedef long long lld;
lld dp[max_n + 5] = {0};
lld sum[max_n + 5] = {0};
int node[max_n + 5] = {0};
lld K[max_n + 5] = {0};
int node_head = 0, node_tail = 0, K_head = 0, K_tail = 0;

lld f(lld x) {
    return dp[x] + sum[x] * sum[x];
}

lld k(lld l, lld j) {
    return (f(j) - f(k)) / (sum[j] - sum[k]);
}

void update() {
    if (K_tail == K_head) {
        Ktail++;
        node_tail++;
        return ;
    } else if (K[K_tail] >= K[K_tail - 1]) {
        K_tail++;
        node_tail++;
        return;
    } else if (K[K_tail] < K[K_tail - 1]) {
        node[node_tail - 1] = node[node_tail];
        node_tail--;
        K_tail--;
        K[K_tail] = k(node[node_tail - 1], node[node_tail]);
    }
}

int main()
{
    int n, M;
    scanf("%d%d", &n, &M);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &sum[i]);
        sum[i] += sum[i - 1];
    }

    node[node_tail] = 0;
    node_tail++;
    dp[1] = sum[1] * sum[1] + M;
    node[node_tail] = 1;
    node_tail++;
    K[K_tail] = k(0,1);
    K_tail++;

    for (int i = 2; i <= n; i++) {
        //找到2sum[i]在斜率中的位置
        int j;
        for (j = K_head; j < K_tail; j++) {
            if (K[j] > 2 * sum[i]) break;
        }
        K_head = j;
        if (K[j] < 2 * sum[i]) {
            dp[i] = dp[j] + (sum[i] - sum[j]) * (sum[i] - sum[j]) + M;
            node[node_tail] = i;
            K[K_tail] = k(node_tail - 1, i);
            update();
        }
        //计算得出dp[i]
        //更新栈
    }

    return 0;
}
