/*************************************************************************
	> File Name: solve.cpp
	> Author: hug
	> Mail:   hug@haizeix.com
	> Created Time: Tue Dec 11 13:30:03 2018
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>
using namespace std;

#define MAX_N 1000000

struct BigNum {
    int *num;
    BigNum() {
        num = (int *)calloc(MAX_N + 5, sizeof(int));
    }
    BigNum(const BigNum &obj) : BigNum() {
        this->operator=(obj);
    }
    void set(int k) {
        num[0] = 0;
        do {
            num[++num[0]] = k % 10;
            k /= 10;
        } while (k);
        return ;
    }
    BigNum operator*(int k) {
        BigNum temp(*this);
        for (int i = 1; i <= temp.num[0]; i++) {
            temp.num[i] *= k;
        }
        for (int i = 1; i <= temp.num[0]; i++) {
            if (temp.num[i] < 10) continue;
            temp.num[i + 1] += temp.num[i] / 10;
            temp.num[i] %= 10;
            temp.num[0] += (i == temp.num[0]);
        }
        return temp;
    }
    BigNum operator+(const BigNum &obj) {
        BigNum temp(*this);
        int len = max(obj.num[0], temp.num[0]);
        for (int i = 1; i <= len; i++) {
            temp.num[i] += obj.num[i];
        }
        temp.num[0] = len;
        for (int i = 1; i <= temp.num[0]; i++) {
            if (temp.num[i] < 10) continue;
            temp.num[i + 1] += temp.num[i] / 10;
            temp.num[i] %= 10;
            temp.num[0] += (i == temp.num[0]);
        }
        return temp;
    }
    BigNum &operator=(const BigNum &obj) {
        memcpy(num, obj.num, sizeof(int) * (MAX_N + 5));
        return *this;
    }
    ~BigNum() {
        free(num);
    }
};

BigNum ans[3], a, b;

ostream &operator<<(ostream &out, BigNum &obj) {
    for (int i = obj.num[0]; i >= 1; --i) {
        out << obj.num[i];
    }
    return out;
}

int main() {
    int n, k;
    cin >> n >> k;
    ans[1].set(k);
    ans[2].set(k * (k - 1));
    ans[0].set(k * (k - 1) * (k - 2));
    for (int i = 4; i <= n; i++) {
        a = ans[(i - 1) % 3] * (k - 2);
        b = ans[(i - 2) % 3] * (k - 1);
        ans[i % 3] = a + b;
    }
    cout << ans[n % 3] << endl;
    return 0;
}
