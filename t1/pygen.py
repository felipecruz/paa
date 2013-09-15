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

    f.close()

if __name__ == "__main__":
    for i in range(10):
        size = 1000 * (2 ** i)
        print(size)
        gen_list(size)
