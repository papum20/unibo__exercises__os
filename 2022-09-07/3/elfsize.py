#!/usr/bin/env python3

import sys
import os


def isElf(path):
    ret = False
    try:
        with open(path, "rb") as f:
            if f.readline()[:4] == b'\x7fELF':
                ret = True
    except:
        pass
    return ret
    
def countElfSize(path):
    if os.path.isdir(path):
        size = 0
        for file in os.listdir(path):
            fullFile = os.path.join(path, file)
            if isElf(fullFile):
                size += os.stat(fullFile).st_size
            elif os.path.isdir(fullFile):
                size += countElfSize(fullFile)
        return size
            
    else:
        return 0

def countElfSize_rec(path):
    if os.path.isdir(path):
        return sum([countElfSize_rec(os.path.join(path,f)) for f in os.listdir(path)], 0)
    elif isElf(path):
        return os.stat(path).st_size
    else:
        return 0



dirs = [os.getcwd()] if len(sys.argv) <= 1 else sys.argv[1:]
print(dirs)

size = sum([countElfSize_rec(d) for d in dirs], 0)
print(size)
