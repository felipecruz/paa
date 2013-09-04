from radix_sort import radix_sort

def counting_sort(A, r, k):
    C = [0] * k
    D = [None] * r
    for i, el in enumerate(A):
        C[A[i]] += 1
    for i in range(k):
        if i > 0:
            C[i] = C[i] + C[i - 1]
    for el in reversed(A):
        D[C[el]-1] = el
        C[el] -= 1
    return D

def quicksort(A):
    if len(A) == 0:
        return []

    if len(A) == 1:
        return A

    n = len(A)
    x = A[n/2]
    L = []
    R = []

    i = 0
    while i < n:
        if A[i] < x:
            L.append(A[i])
        elif A[i] > x:
            R.append(A[i])
        i += 1

    return quicksort(L) + [x] + quicksort(R)

import time
import copy
import numpy.random as nprnd

numbers = nprnd.randint(1000, size=20000)

n1 = time.time()
r1 = radix_sort(copy.copy(numbers), 3)
n2 = time.time()
print("Radix {0}".format(n2 - n1))

n1 = time.time()
r2 = sorted(copy.copy(numbers))
n2 = time.time()
print("Native sorted: {0}".format(n2 - n1))

n1 = time.time()
r3 = quicksort(copy.copy(numbers))
n2 = time.time()
print("Python quiksort: {0}".format(n2 - n1))
