import random
import sys

def generate_b_instances(i):
    swaps = 2 ** i
    size = 2 ** 25
    numbers = []
    for i in xrange(size):
        numbers.append(i+1)
    for i in xrange(swaps):
        rand_index_1 = random.randint(1, size - 1)
        rand_index_2 = random.randint(1, size - 1)
        temp = numbers[rand_index_1]
        numbers[rand_index_1] = numbers[rand_index_2]
        numbers[rand_index_2] = temp

    f = open('B_%d.txt' % swaps, 'w')
    for number in iter(numbers):
        f.write('%d\n' % number)
    f.close()

def generate_a_instances(size):
    f = open('py%d.txt' % size, 'w')
    i = 0
    r = 0
    number_tracker = {}

    while i < size:
        number = random.randint(1, size)
        r += 1
        if not number in number_tracker:
            f.write('%d\n' % number)
            i += 1
            number_tracker[number] = True

    print("Comps for size:%d is %d" % (size, r))
    f.close()

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Use: python generate_instance.py {A,B} i")
    else:
        if sys.argv[1] == "A":
            i = int(sys.argv[2])
            size = 1000 * (2 ** i)
            print("Instance %d size: %d" % (i, size))
            generate_a_instances(size)
        elif sys.argv[1] == "B":
            i = int(sys.argv[2])
            size = 2 ** 25
            swaps = 2 ** i
            generate_b_instances(i)
        else:
            print("Use: python generate_instance.py {A,B} i")
