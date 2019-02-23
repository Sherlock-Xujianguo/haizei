#!/usr/bin/env python
# coding=utf-8
from random import randint

n = int(input())

for i in range(n):
    num = randint(ord('a'),ord('z'))
    print(chr(num), end='')
print('')
