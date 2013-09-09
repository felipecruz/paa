import collections
import functools

class memoized(object):
   '''Decorator. Caches a function's return value each time it is called.
   If called later with the same arguments, the cached value is returned
   (not reevaluated).
   '''
   def __init__(self, func):
      self.func = func
      self.cache = {}
   def __call__(self, *args):
      if not isinstance(args, collections.Hashable):
         # uncacheable. a list, for instance.
         # better to not cache than blow up.
         return self.func(*args)
      if args in self.cache:
         return self.cache[args]
      else:
         value = self.func(*args)
         self.cache[args] = value
         return value
   def __repr__(self):
      '''Return the function's docstring.'''
      return self.func.__doc__
   def __get__(self, obj, objtype):
      '''Support instance methods.'''
      return functools.partial(self.__call__, obj)

@memoized
def get_digit(digit, i):
    if digit == 0:
        return 0
    if digit:
        return int((digit / 10 ** i) % 10)
    raise Exception("Bad Digit {0}".format(digit))


assert 0 == get_digit(100, 0)
assert 0 == get_digit(100, 1)
assert 1 == get_digit(100, 2)
assert 1 == get_digit(110, 1)
assert 2 == get_digit(12, 0)


def counting_sort_by_digit(A, r, n):
    C = [0] * 10
    D = [None] * r
    for i in range(r):
        C[get_digit(A[i], n)] += 1
    for i in range(10):
        if i > 0:
            C[i] = C[i] + C[i - 1]
    for el in reversed(A):
        el_index = get_digit(el, n)
        D[C[el_index]-1] = el
        C[el_index] -= 1
    return D

def radix_sort(A, r):
    len_a = len(A)
    for i in range(r):
        A = counting_sort_by_digit(A, len_a, i)
    return A


import time
import copy
import numpy.random as nprnd

numbers = nprnd.randint(1000, size=20000)

assert radix_sort(copy.copy(numbers), 4) == sorted(copy.copy(numbers))
