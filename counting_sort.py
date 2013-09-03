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

numbers = [1, 2, 3, 1, 2, 3, 4, 4, 3, 3, 2, 1, 0, 1, 9, 8, 7, 1, 0, 1]
print(counting_sort(numbers, len(numbers), 10))
