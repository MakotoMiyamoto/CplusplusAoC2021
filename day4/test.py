import subprocess
import timeit
import sys

def pipe(*vargs):
    subprocess.run((vargs), stdout=subprocess.DEVNULL)

argv = [f"'{arg}'," for arg in sys.argv[1:]]

print(int(timeit.timeit(f"pipe({' '.join(argv)[:-1]})", number=1, globals=globals()) * 1000), "ms");
