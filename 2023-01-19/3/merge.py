import sys
import os

def copy_all(src, dst):
    src = src.strip('/')
    dst = dst.strip('/')

    for path, dirs, files in os.walk(src):
        if path.find(f'{src}/') != -1:
            rel_path = path[(path.find(f'{src}/') + len(src)):]
        elif path.strip('.').strip('/') == src:
            rel_path = ''
        else:
            rel_path = path.strip('.')
        rel_path = rel_path.strip('/')
        print(f'rel path: {rel_path}')
        # mk missing dirs
        for d in dirs:
            print(f'dir: {d}')
            p = os.path.join(dst, rel_path, d)
            print(f'dir newpath: {p}')
            if not os.path.exists(p):
                os.mkdir(p)
        # copy files append
        for file in files:
            print(f'file: {file}')
            # read
            with open(os.path.join(path, file), "r") as fr:
                # write
                p = (os.path.join(dst, rel_path, file))
                print(f'p for write: {p}')
                with open(p, "a") as fw:
                    for line in fr.readlines():
                        fw.write(line)



if len(sys.argv) < 4:
    print("missing args")
    exit(1)

a, b, c = sys.argv[1:4]
print(a,b,c)

copy_all(a, c)
copy_all(b, c)
