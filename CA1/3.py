n = int(input())
divisors = [[] for i in range(1, 100010)]
cnt = [0 for i in range(1, 100010)]
for i in range(1, 100002):
    for j in range(i, 100002, i):
        divisors[j].append(i)
for i in range(1, n + 1):
    type, x = map(int, input().split())
    if(type == 1):
        for j in range(0, len(divisors[x])):
            cnt[divisors[x][j]] += 1
    else:
        print(cnt[x])