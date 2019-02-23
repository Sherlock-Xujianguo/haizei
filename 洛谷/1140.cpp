#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
#define max_n 100
#define INF 0x3f3f3f3f

int match[5][5] = {
    {5, -1, -2, -1, -3}, 
    {-1, 5, -3, -2, -4},
    {-2, -3, 5, -2, -2},
    {-1, -2, -2, 5, -1},
    {-3, -4, -2, -1, 0}
};

int dna1[max_n + 5] = {0};
int dna2[max_n + 5] = {0};

int dp[max_n + 5][max_n + 5];

int main()
{
    for (int i = 0; i < max_n; i++) {
        for (int j = 0; j < max_n; j++)
            dp[i][j] = -INF;
    }

    int m, n;
    cin >> m;
    getchar();
    for (int i = 1; i <= m; i++) {
        char c;
        cin >> c;
        switch (c) {
        case 'A': 
            dna1[i] = 0; 
            break;
        case 'C':
            dna1[i] = 1;
            break;
        case 'G':
            dna1[i] = 2;
            break;
        case 'T':
            dna1[i] = 3;
            break;
        }
    }
    getchar();
    cin >> n;
    for (int i = 1; i <= n; i++) {
        char c;
        cin >> c;
        switch (c) {
        case 'A': 
            dna2[i] = 0; 
            break;
        case 'C':
            dna2[i] = 1;
            break;
        case 'G':
            dna2[i] = 2;
            break;
        case 'T':
            dna2[i] = 3;
            break;
        }
    }
    dp[0][0] = 0;  
    for (int i = 1; i <= m; i++) dp[i][0] = dp[i - 1][0] + match[dna1[i]][4];
    for (int j = 1; j <= n; j++) dp[0][j] = dp[0][j - 1] + match[4][dna2[j]];
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            dp[i][j] = max(dp[i][j], dp[i][j - 1] + match[dna2[j]][4]);
            dp[i][j] = max(dp[i][j], dp[i - 1][j] + match[4][dna1[i]]);
            dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + match[dna1[i]][dna2[j]]);
        }
    }

    cout << dp[m][n] << endl;
    return 0;
}

