n = int(input())
a = list(map(int, input().split()))
lim = input()
max = 0
ans_string = []
index = -1
par_sum = [0 for i in range(0, n + 1)]
for i in range(n - 1, -1, -1):
    par_sum[i] = par_sum[i + 1]
    if(a[i] > 0):
        par_sum[i] += a[i]
now = 0
for i in range(0, n + 1):
    ans = 0
    if(i != n):
        ans = par_sum[i + 1]
    ans += now
    if(i != n):
        now += a[i] * int(lim[i])
    if(ans >= max or index == -1):
        if(i == n or lim[i] == "1"):
            max = ans
            index = i
for i in range(0, index):
    ans_string.append(lim[i])
if(index != n):
    ans_string.append(0)
for i in range(index + 1, n):
    if(a[i] < 0):
        ans_string.append(0)
    else:
        ans_string.append(1)
for i in range(0, len(ans_string)):
    print(ans_string[i], end = '')
print()
print(max)