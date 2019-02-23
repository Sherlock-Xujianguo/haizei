/*================================================================
*   
*   
*   文件名称：solve.cpp
*   创 建 者：Sherlock_XuJianguo
*   创建日期：2019年01月03日
*   描    述：
*
================================================================*/

#include <iostream>
#include <vector>
#include <string.h>
#define max_n 500000
using namespace std;

char s[max_n + 5];
string str;
vector<int> h[max_n + 5];
int dp[max_n + 5];

int main()
{
    cin >> str;
    int n = str.length();
    for (int i = 0; i < n; i++) s[i + 1] = str[i];
    for (int i = 1; i <= n; i++) dp[i] = max_n + 5;

    h[1].push_back(1);

    for (int i = 2; i <= n; i++) {
        h[i].push_back(i);
        if (s[i] == s[i - 1]) h[i].push_back(i - 1);
        for (int j = 0; j < h[i - 1].size(); j++) {
            int k = h[i - 1][j];
            if (s[k - 1] == s[i]) h[i].push_back(k - 1);
        }
    }

    dp[0] = -1;
    dp[1] = 0;
    for (int i = 2; i<= n; i++) {
        for (int j = 0; j < h[i].size(); j++) dp[i] = min(dp[i], dp[h[i][j] - 1] + 1);
    }

    cout << dp[n] << endl;

    return 0;
}
