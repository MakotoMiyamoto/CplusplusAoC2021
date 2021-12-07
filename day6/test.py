import subprocess
import timeit
import sys

def pipe(*vargs):
    subprocess.run((vargs), stdout=subprocess.DEVNULL)

argv = " ".join(sys.argv[1:])

start = timeit.default_timer()
for i in range(10):
    pipe(argv)
end = timeit.default_timer()

print("Avg. time elapsed: ~", int((end-start) * 1000 / 10), "ms", sep="")
