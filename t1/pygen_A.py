import random

def gen_list(size):
    f = open('py%d.txt' % size, 'w')
    i = 0
    number_tracker = {}

    while i < size:
        number = random.randint(1, size)
        if not number in number_tracker:
            f.write('%d\n' % number)
            i += 1
            number_tracker[number] = True
        if i % 1000 == 0:
            print("Missing %d" % (size - i))

    f.close()

if __name__ == "__main__":
    for i in range(1, 16, 1):
        size = 1000 * (2 ** i)
        print("Instance %d size: %d" % (i, size))
        gen_list(size)
