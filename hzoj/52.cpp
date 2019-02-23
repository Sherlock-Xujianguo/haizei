#include <stdio.h>
#include <math.h>
#include <inttypes.h>
#define max_n 1000000

typedef long long lld;
lld min(lld a, lld b)
{
    return (a > b) ? b : a;
}

lld dp[max_n+5]={0};
lld C[max_n + 5] = {0};
lld sum[max_n + 5] = {0};
int main()
{
    int n, M;
    scanf("%d%d", &n, &M);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &C[i]);
        sum[i] = sum[i - 1] + C[i];
    }
    for (int i = 1; i <= n; i++) {
        dp[i] = INT64_MAX;
        for (int j = 0; j <= i - 1; j++) {
            dp[i] = min(dp[i],dp[j]+pow(sum[i]-sum[j],2)+M);
        }
    }
    printf("%lld\n", dp[n]);
    
    return 0;
}
