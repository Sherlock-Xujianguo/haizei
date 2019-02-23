#include <stdio.h>
#include <inttypes.h>

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

int main()
{

    int n;
    scanf("%d", &n);
    
    int a[3][100] = {0};
    a[0][0] = a[2][0] = a[1][0] = a[1][1] = 1;
    a[2][1] = 2;
    a[0][1] = 3;
    for (int i = 3; i <= n; i++) {
        add(a[i % 3], a[(i - 1) % 3], a[(i - 2) % 3]);
    }

    print(a[n % 3]);
    

    return 0;
}
