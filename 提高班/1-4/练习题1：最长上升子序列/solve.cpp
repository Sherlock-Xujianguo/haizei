/*================================================================
*   
*   文件名称：solve.cpp
*   创 建 者：Sherlock_XuJianguo
*   创建日期：2018年12月31日
*   描    述：
*
================================================================*/

#include <stdio.h>
#include <iostream>

#define MAX_N 500000

using namespace std;

void binary_search(int *num, int *low, int *high, int key){
    
    int mid = (*low + *high) >> 1;

    if (*low == *high || *high - *low == 1) return ;
    
    if (num[mid] > key) {
        *high = mid;
        binary_search(num, low, high, key);
    } else if (num[mid] < key) {
        *low = mid;
        binary_search(num, low, high, key);
    } else {
        *low = *high = mid;
        return ;
    }
    return ;
}


int main()
{
    int n;
    int stack[MAX_N] = {0}, len = 1;
    stack[0] = -1;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int low = 0, high = len - 1;
        int temp;
        cin >> temp;

        binary_search(stack, &low, &high, temp);
        if (low == high && low != 0) continue;
        
        if (low == high || high == len - 1 && stack[high] < temp) {
            stack[len] = temp;
            len++;
        } else if (stack[high] > temp && stack[low] < temp) {
            stack[high] = temp;
        } else continue;
        
    }

    cout << len - 1 << endl;
    

    return 0;
}
