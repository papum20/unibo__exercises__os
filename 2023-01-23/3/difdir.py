#!/usr/bin/env python3
from sys import argv
import os



def cp(src, dst):
    lines = []
    with open(src, 'r') as f:
        lines = f.readlines()
    with open(dst, 'w') as f:
        f.write('\n'.join(lines))


if len(argv) != 5:
    exit(1)

a, b, newa, newb = argv[1:]
print(a, b, newa, newb)


if not os.path.isdir(newa):
    os.mkdir(newa)
if not os.path.isdir(newb):
    os.mkdir(newb)

for file in os.listdir(a):
    if os.path.exists(os.path.join(b, file):
        cp(os.path.join(a, file), os.path.join(newa, file))
        cp(os.path.join(b, file), os.path.join(newb, file))
