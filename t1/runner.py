import io
import os
import subprocess
import sys

BUFF_SIZE = 8 * 1024

command = "./benchmark %d %d %d %d"

def run(command):
    r, w = os.pipe()

    p = subprocess.Popen(command, shell=True, stdout=w, stderr=w)

    a, b = p.communicate()
    sio = io.StringIO()

    while True:
        buf = os.read(r, BUFF_SIZE)
        sio.write(buf.decode('utf-8'))
        if len(buf) < BUFF_SIZE:
            break

    print(sio.getvalue())


for a in range(4, 1, -1):
    for k in range(1, 5, 1):
        for i in range(1, 16, 1):
            run(command % (a, k, 1, i))
        for i in range(1, 26, 1):
            run(command % (a, k, 2, i))
