import os
from sys import argv


DIR = argv[1]
FILES = os.listdir(DIR)

print(DIR)
print(FILES)

count = []
for FILE in FILES:
    with open(f'{DIR}/{FILE}', 'r') as fd:
        for (n, val) in enumerate(fd.readlines()):
            if len(count) < n + 1:
                count.append(len(val) - 1) 
            else:
                count[n] += len(val) - 1

for (n,c) in enumerate(count):
    print(f'{n+1} {c}')
