#include <iostream>
#include <stdio.h>
#include <algorithm>
#define max_n 5000
using namespace std;

typedef struct stick {
    int l;
    int w;
};
stick s[max_n + 5];
int n;

int comp(const stick &s1, const stick &s2) {
    return s1.l > s2.l;
}

int main()
{
    cin >> n;
    for (int i = 0; i < n ; i++ ) {
        cin >> s[i].l;
        cin >> s[i].w;
    }
    sort(s, s + n, comp);
    
    int rec[max_n + 5] = {0};
    int rst = 0;
    for (int i = 0; i < n; i++) {
        if (rec[i] == 1) continue;
        rst++;
        int flag = s[i].w;
        for (int j = i + 1; j < n; j++) {
            if (rec[j] == 1) continue;
            if (s[j].w <= flag) {
                rec[j] = 1;
                flag = s[j].w;
            } 
        }
    }
    cout << rst << endl;
    return 0;
}

