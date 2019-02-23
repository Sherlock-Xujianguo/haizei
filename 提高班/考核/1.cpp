#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#define max_n 1000
using namespace std;

int f[3][1000] = {0};

void add(int *num1, int *num2, int *ans) {
    int len = max(num1[0], num2[0]);
    ans[0] = len;
    for (int i = 1; i <= len; i++) {
        ans[i] = num1[i] + num2[i];
    }
    for (int i = 1; i <= len; i++) {
        if (ans[i] < 10) continue;
        ans[i + 1] += ans[i] / 10;
        ans[i] %= 10;
        if (i == len) ans[0] += (ans[i + 1] != 0);
    }
}

void mul(int *num, int n, int *ans) {
    for (int i = 1; i <= num[0]; i++) {
        num[i] *= n;
    }
    for (int i = 1; i <= num[0]; i++) {
        if (num[i] < 10) continue;
        num[i + 1] += num[i] / 10;
        num[i] %= 10;
        if (i == num[0]) num[0] += (num[i + 1] != 0);
    }
    for (int i = 0; i <= num[0]; i++) ans[i] = num[i];
}

void set(int *num, int k) {
    if (k < 10) {
        num[0] = 1;
        num[1] = k;
    } else {
        num[0] = 2;
        num[1] = k % 10;
        num[2] = k / 10;
    }
}

void print(int *num) {
    for (int i = num[0]; i >= 1; i--) printf("%d", num[i]);
    printf("\n");
}

int main()
{
    int n, k;
    cin >> n >> k;
    set(f[1], 0);
    set(f[2], k*(k-1));
    for (int i = 3; i <= n; i++) {
        int num1[1000];
        int num2[1000];
        mul(f[(i - 2) % 3], k - 1, num1);
        mul(f[(i - 1) % 3], k - 2, num2);
        add(num1, num2, f[i % 3]);
    }
    print(f[n % 3]);
    return 0;
}

