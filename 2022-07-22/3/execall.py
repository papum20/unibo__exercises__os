import sys, os

path = '.' if len(sys.argv) < 2 else sys.argv[1]

for root, dirs, files in os.walk(path):
    for file in files:
        print(os.path.join(root,file),os.stat(os.path.join(root, file)))
        
