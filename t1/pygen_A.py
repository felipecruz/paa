import random
import sys

def gen_list(size):
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
    if len(sys.argv) < 2:
        print("Especificar o valir de i")
    else:
        i = int(sys.argv[1])
        size = 1000 * (2 ** i)
        print("Instance %d size: %d" % (i, size))
        gen_list(size)
