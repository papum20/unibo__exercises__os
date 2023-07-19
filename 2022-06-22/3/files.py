import subprocess
import os


for f in os.listdir():
    print(f)
    subprocess.run(["file", f], capture_output=True)

