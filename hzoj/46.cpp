#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#define max_n 500000
using namespace std;

int dp[max_n + 5] = {0};
vector <int> h[max_n + 5];
int main()
{
    char s[max_n + 5];
    memset(s, 0, sizeof(s));
    string str;
    cin >> str;
    for (int i = 1; i <= str.length(); i++) s[i] = str[i - 1];
    
    dp[0] = -1;
    dp[1] = 0;
    for (int i = 2; i <= str.length(); i++) {
        dp[i] = INT32_MAX;
        h[i].push_back(i);
        if (s[i] == s[i - 1]) h[i].push_back(i - 1);
        for (int j = 0; j < h[i - 1].size(); j++) {
            if (s[i] == s[h[i - 1][j] - 1]) {
                h[i].push_back(h[i - 1][j] - 1);
            }
        }
        for (int j = 0; j < h[i].size(); j++) {
            dp[i] = min(dp[i], dp[h[i][j] - 1] + 1);
        }
    }
    cout << dp[str.length()] << endl;
    return 0;
}

