n = int(input())

for counter in range(n):
	s = input()
	possible = False
	for i in range(len(s) + 1):
		tmp = s[0 : i] + '#' + s[i : len(s)]
		length = len(tmp)
		can = True

		for j in range(length):
			if tmp[j] != tmp[length - j - 1] and tmp[j] != '#' and tmp[length - j - 1] != '#':
				can = False
				break
		possible |= can

	if possible:
		print("YES")
	else:
		print("NO")
