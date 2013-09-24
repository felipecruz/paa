import random

def gen_list(size):
    swaps = 2 ** size
    size = 2 ** 25
    numbers = []
    for i in xrange(size):
        numbers.append(i)
    for i in xrange(swaps):
        rand_index_1 = random.randint(1, size - 1)
        rand_index_2 = random.randint(1, size - 1)
        temp = numbers[rand_index_1]
        numbers[rand_index_1] = numbers[rand_index_2]
        numbers[rand_index_2] = temp

    f = open('B_%d.txt' % size, 'w')
    for number in iter(numbers):
        f.write('%d\n' % number)
    f.close()

if __name__ == "__main__":
    for i in range(1, 26, 1):
        print("Position swaps %d" % (2 ** i))
        gen_list(i)
