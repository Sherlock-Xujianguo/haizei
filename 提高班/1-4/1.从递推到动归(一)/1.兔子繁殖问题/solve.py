#!/usr/bin/env python
# coding=utf-8

n = int(raw_input())
a, b, c = 1, 1, 2
for i in xrange(0, n):
    c = a + b
    a = b
    b = c
print a

