#include <stdio.h>

int rec[4][100] = {0};

int max(int a, int b) {
    return (a > b) ? a : b;
}

void add(int *ans, int *a, int *b) {
    int len = max(a[0], b[0]);
    ans[0] = len;
    for (int i = 1; i <= len; i++) {
        ans[i] = a[i] +b[i];
    }
    for (int i = 1; i <= len; i++) {
        if (ans[i] < 10) continue;
        ans[i + 1] += ans[i] / 10;
        ans[i] %= 10;
        if (i == len) ans[0] += ans[len + 1];
    }
}

void print(int *ans) {
    for (int i = ans[0]; i > 0; i--)
        printf("%d", ans[i]);
    printf("\n");
}



int main() {
    int n;
    scanf("%d", &n);

    rec[0][0] = rec[1][0] = rec[2][0] = rec[3][0] = 1;
    rec[2][1] = rec[3][1] = rec[0][1] = 1;

    for (int i = 4; i <= n; i++) {
        add(rec[i % 4], rec[(i - 2) % 4], rec[(i - 3) % 4]);
    }
    print(rec[n % 4]);
    return 0;
}
