#include <iostream>
#include <stdio.h>
#include <stdlib.h>

int dp[205][10] = {0};

void init()
{
    for (int i = 0; i <= 200; i++) 
        dp[i][1] = 1;
}

int main()
{
    init();
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 0; i <= 200; i++) {

    }
    return 0;
}

