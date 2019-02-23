#include <iostream>
#define max_n 50000
using namespace std;
int weight[max_n + 5];
int value[max_n + 5];
int f[max_n + 5];
int max(int a, int b) {
    return a > b ? a : b;
}
int main() {
    int n, m;
    cin >> n;
    cin >> m;
    for (int i = 1; i <= n; i++) {
        cin >> weight[i] >> value[i];
    }

    for (int i = 1; i <= n; i++) {
        for (int j = weight[i]; j <= m; j++) {
            f[j] = max(f[j], f[j - weight[i]] + value[i]);
        }
    }
    cout << f[m] << endl;
}
