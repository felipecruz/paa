def logn_power(x, n):
    if n == 0:
        return 1
    elif n == 1:
        return x

    _n = n / 2
    if n % 2:
        return logn_power(x, _n) * logn_power(x, _n) * x
    else:
        return logn_power(x, _n) * logn_power(x, _n)

for i in range(11):
    for j in range(11):
        print("{v} == pow({i}, {j}) == logn_power({i}, {j})"
                ).format(i=i, j=j, v=pow(i, j))
        assert pow(i, j) == logn_power(i, j)
