
import math
X = [2.0, 2.3, 2.5, 3.0, 3.5, 3.8, 4.0]
fx = [5.848, 6.127, 6.300, 6.694, 7.047, 7.243, 7.368]


def w(x):
    prod = 1
    for item in X:
        prod *= (x-item)
    return prod


def wj(i: int, x):
    prod = 1
    for idx, item in enumerate(X):
        if idx == i:
            continue
        prod *= X[i]-item
    return prod


def ln(x):
    w_result = w(x)
    result = 0
    for idx, item in enumerate(X):
        result += (w_result * fx[idx])\
            / ((x-item)*wj(idx, item))
    return result


def remainder(x):
    return fx[-1]*w(x)/math.factorial(len(X))


d = 3.75
ln_res = ln(d)
ln_rem = remainder(d)
print(f"{ln_res:.8f} {ln_rem:.8f}")
