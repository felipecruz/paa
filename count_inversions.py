def _min(a, b):
    if a == None:
        return b
    elif b == None:
        return a
    else:
        return min(a, b)

def _get_empty(_list, i):
    try:
        return _list[i]
    except IndexError:
        return None

def merge(left, right):
    result = []
    i = j = 0
    inversions = 0
    while i + j < len(left) + len(right):
        l = _get_empty(left, i)
        r = _get_empty(right, j)
        m = _min(l, r)
        if m == l:
            i += 1
        else:
            j += 1
            if i <= len(left):
                inversions += len(left) - i

        result.append(m)

    return (result, inversions)

def count_inv(items):
    if len(items) == 1:
        return (0, items)

    half = len(items) / 2

    items_a = items[:half]
    items_b = items[half:]

    (x, merged_left) = count_inv(items_a)
    (y, merged_right) = count_inv(items_b)

    a, z = merge(merged_left, merged_right)

    inv = x + y + z

    return (inv, a)

assert ([1, 2, 3], 0) == merge([1, 2], [3])
assert ([1, 2, 3], 1) == merge([1, 3], [2])
assert ([1, 2, 3, 4], 0) == merge([1, 2], [3, 4])
assert ([1, 2, 3, 4], 4) == merge([3, 4], [1, 2])
assert ([1, 2, 3, 4], 3) == merge([2, 4], [1, 3])

assert 3 == count_inv([1, 3, 5, 2, 4, 6])[0]
assert 1 == count_inv([2, 1])[0]
assert 2 == count_inv([2, 3, 1])[0]
assert 3 == count_inv([3, 2, 1])[0]
