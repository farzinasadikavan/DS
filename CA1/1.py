n, k = [int(x) for x in input().split()]
a = [int(x) for x in input().split()]

maximum = 0
for x in a:
	maximum = max(maximum, x)
max_divider = maximum + k // n + 1

for i in range(max_divider, 1, -1):
	need = 0
	for x in a:
		if x % i != 0:
			need += i - (x%i)
		if need > k:
			break
	if need <= k:
		print(i)
		exit()