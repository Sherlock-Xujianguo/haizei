#-*- coding:utf-8 -*-

import random

n = int(input())
num = []

print(n)

for i in range(n):
    num.append(random.randint(0,10000))
    if i == n - 1:
        print(num[i])
    else:
        print(str(num[i])+' ',end='')
