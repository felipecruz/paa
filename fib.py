def fib_n(factor):
    if factor == 0:
        return 0
    if factor == 1:
        return 1
    if factor == 2:
        return 1
    if factor == 3:
        return 2

    n1 = 1
    n2 = 2
    acc = 0

    for i in range(factor-3):
        acc = n1 + n2
        n1 = n2
        n2 = acc

    return acc

print(fib_n(0))
print(fib_n(1))
print(fib_n(2))
print(fib_n(3))
print(fib_n(4))
print(fib_n(5))
print(fib_n(6))
print(fib_n(7))
print(fib_n(200))
print(fib_n(200000))
