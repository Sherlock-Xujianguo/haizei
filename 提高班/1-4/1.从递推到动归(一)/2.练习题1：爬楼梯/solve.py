#!/usr/bin/env python
# coding=utf-8

n = int(raw_input())
a, b, c, d = 0, 1, 1, 1
for i in xrange(1, n):
    d = a + b
    a = b
    b = c
    c = d
print a

