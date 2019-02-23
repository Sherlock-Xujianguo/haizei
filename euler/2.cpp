#include <iostream>

int main()
{
    int f[3] = {0};
    f[1] = 1;
    f[2] = 2;
    f[0] - 0;
    long long ans = 0;
    ans += 2;
    for (int i = 3; ; i++) {
        f[i % 3] = f[(i - 1) % 3] + f[(i - 2) % 3];
        printf("%d\n", f[i%3]);
        if (f[i % 3] > 4000000) break;
        if (f[i % 3] & 1) continue;
        ans += f[i % 3];
    }
    printf("%d\n", ans);
    return 0;
}

