#!/usr/bin/env python
# coding=utf-8

from random import randint
m = randint(10, 20)
n = randint(200, 10000)

print m, n
list_a = []
now = randint(1, 10)
for i in xrange(0, m):
    list_a.append(now)
    now += randint(1, 10)

