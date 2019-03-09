#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#define max_n 100
struct book {
    int height;
    int width;
} books[max_n + 5] = {0};

bool cmp(struct book &a, struct book &b) {
    return (a.height < b.height);
}
using namespace std;
int main()
{
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> books[i].height >> books[i].width;
    }
    sort(books, books + n, cmp);
    
    
    return 0;
}

