#include <iostream>
#include <stdio.h>
#define max_n 1000000
using namespace std;

int num[max_n + 5] = {0};
int sta[max_n + 5] = {0};

int binary_search(int low, int high, int key) {
    while(low < high) {
        int mid = ((low + high) / 2) + ((low + high) % 2);
        if (sta[mid] == key) return mid;
        else if (sta[mid] > key) high = mid - 1;
        else low = mid;
    }
    return low;
}

int len(int *n) {
    int i;
    for (i = 0; n[i] != 0; i++)
        continue;
    return i;
}

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> num[i];
    sta[0] = -1;

    for (int i = 0; i < n; i++) {
        int k = binary_search(0, len(sta), num[i]);
        sta[k] = num[i];
    }
    printf("%d\n", len(sta));
    return 0;
}

