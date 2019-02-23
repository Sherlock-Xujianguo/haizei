#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
#define max_n 100000
#define INF 0x3f3f3f3f

struct Point{
    int x, y;
    int dis1, dis2;
    void set(int x1, int y1, int x2, int y2) {
        dis1 = (x1 - x) * (x1 - x) + (y1 - y) * (y1 - y);
        dis2 = (x2 - x) * (x2 - x) + (y2 - y) * (y2 - y);
    }
} point[max_n + 5];

bool cmp(struct Point &a, struct Point &b) {
    return a.dis1 < b.dis1;
}

int main()
{
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> point[i].x >> point[i].y;
        point[i].set(x1, y1, x2, y2);
    }
    sort(point, point+n, cmp);
    int ans = point[n - 1].dis1, temp = point[n - 1].dis2;
    for (int i = n - 2; i >= 0; i--) {
        if (point[i].dis1 + temp < ans) {
            ans = point[i].dis1 + temp;
        }
        temp = max(temp, point[i].dis2);
    }
    ans = min(ans, temp);
    cout << ans << endl;
    return 0;
}

