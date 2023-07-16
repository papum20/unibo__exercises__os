import sys
import os

def copy_all(src, dst):
    src = src.strip('/')
    dst = dst.strip('/')

    for path, dirs, files in os.walk(src):
        rel_path = path[(path.find(src) + len(src):]
        # mk missing dirs
        for d in dirs:
            p = os.path.join(dst, rel_path, d)
            if not os.path.exists(p):
                os.mkdir(p)
        # copy files append
        for file in files:
            # read
            with open(os.path.join(path, file), "r") as fr:
                # write
                with open(os.path.join(dst, rel_path, file), "a") as fw:
                    



if len(sys.argv) < 4:
    print("missing args")
    exit(1)

a, b, c = sys.argv[1:4]

for 
