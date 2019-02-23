# coding=utf-8

n, k = (int(x) for x in raw_input().split())
ans = [k, k * (k - 1), k * (k - 1) * (k - 2)]
for i in xrange(3, n):
    ans[i % 3] = (k - 2) * ans[(i - 1) % 3] + (k - 1) * ans[(i - 2) % 3]
print ans[(n - 1) % 3]
