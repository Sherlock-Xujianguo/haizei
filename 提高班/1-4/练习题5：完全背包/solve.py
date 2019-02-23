#!/usr/bin/env python
# coding=utf-8

from random import randint

arr = input().split()

n, m = int(arr[0]),int(arr[1])
print(n,m)
for i in range(n):
    c = randint(1,m)
    v = randint(1,m)
    print(c,v)
