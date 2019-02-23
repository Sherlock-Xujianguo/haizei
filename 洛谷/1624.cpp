#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;
#define max_n 150

char valid[105][max_n + 5];
int dp[max_n + 5][2] = {0};

int is_end(string input) {
    char s[10];
    for (int i = 0; i < 9; i++) {
        s[i] = input[i];
    }
    s[9] = '\0';
    if (strcmp(s, "LAST CASE") == 0) return 1;
    else return 0;
}

int is_in(char *abb, char c) {
    for (int i = 0; abb[i]; i++) {
        if (abb[i] == c) return 1;
    }
    return 0;
}

int main()
{
    int n;
    scanf("%d", &n);
    getchar();
    for (int i = 0; i < n; i++) scanf("%s", valid[i]);
    string input;
    while (getline(cin,input)){
        if (is_end(input)) break;
        
    
    }
    return 0;
}

