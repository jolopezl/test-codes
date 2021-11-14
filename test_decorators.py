from numba import jit
import numpy as np


@jit(nopython=True)
def go_fast(a):
    trace = 0.0
    for i in range(a.shape[0]):
        trace += np.tanh(a[i, i])
    return a + trace

def go_slow(a):
    trace = 0.0
    for i in range(a.shape[0]):
        trace += np.tanh(a[i, i])
    return a + trace

def time_it():
    import time
    x = np.arange(100).reshape(10, 10)

    # DO NOT REPORT THIS... COMPILATION TIME IS INCLUDED IN THE EXECUTION TIME!
    start = time.time()
    go_fast(x)
    end = time.time()
    print("Elapsed (with compilation) = %s" % (end - start))

    # NOW THE FUNCTION IS COMPILED, RE-TIME IT EXECUTING FROM CACHE
    start = time.time()
    go_fast(x)
    end = time.time()
    print("Elapsed (after compilation) = %s" % (end - start))

    # NOW THE FUNCTION IS COMPILED, RE-TIME IT EXECUTING FROM CACHE
    start = time.time()
    go_slow(x)
    end = time.time()
    print("Elapsed (slow version) = %s" % (end - start))

time_it()