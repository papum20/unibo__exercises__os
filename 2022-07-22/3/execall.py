import sys, os, subprocess

path = '.' if len(sys.argv) < 2 else sys.argv[1]

def isElf(path):
    ret = False
    try:
        with open(path, "rb") as f:
            if f.readline()[:4] == b'\x7fELF':
                ret = True
    except:
        pass
    return ret
 
for root, dirs, files in os.walk(path):
    for file in files:
        abspath = os.path.abspath(os.path.join(root, file))
        print(abspath)
        permissions = oct(os.stat(abspath).st_mode)[-3:]
        print(permissions, permissions[0])
        print(isElf(abspath))

        if not isElf(abspath) and (int(permissions[0]) % 2 == 1):
            subprocess.run([abspath], shell=True)

    
