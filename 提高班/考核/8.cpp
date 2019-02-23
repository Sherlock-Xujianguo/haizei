#include <iostream>
#include <stdio.h>
#include <string.h>
#define max_n 1000000
using namespace std;

int d(int n) {
    char temp[max_n + 5];
    for (int i = 1; i <= max_n; i++) {
        sprintf(temp, "%d", i);
        if (n > strlen(temp)) n -= strlen(temp);
        else break;
    }
    return temp[n - 1] - '0';
}

int main()
{
    int x, y, z;
    cin >> x >> y >> z;
    cout << d(x) * d(y) * d(z) << endl;
    return 0;
}

