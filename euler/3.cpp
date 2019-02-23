#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;
#define max_n 500000
short prime[max_n + 5] = {0};

int main()
{
    printf("*");
    long long num = 600851475143;
    int max_prime = 2;
    for (int i = 2; i < max_n; i++){
        if (prime[i] == 0) prime[++prime[0]] = i;
        if (num % i == 0) max_prime = i;
        for (int j = 1; j <= prime[0]; j++) {
            if (prime[j] * i < max_n) prime[prime[j] * i] = 1;
            if (i % prime[j] == 0) break;
        }
    }
    printf("%d\n", max_prime);
    return 0;
}

