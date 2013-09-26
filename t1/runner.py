import io
import os
import subprocess
import sys

BUFF_SIZE = 8 * 1024

algos = {
    1: "knth_nk",
    2: "knth_merge",
    3: "knth_n_mom",
    4: "knth_n_quickselect.c"
}

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


for a in range(3, 5, 1):
    for k in range(1, 5, 1):
        #for i in range(1, 16, 1):
        #    run(command % (a, k, 1, i))
        for i in range(14, 26, 1):
            #run("python pygen_B.py %d" % (i))
            run(command % (a, k, 3, i))
