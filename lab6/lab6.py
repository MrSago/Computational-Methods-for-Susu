
from math import sqrt, log


def naive(a, b):
    return log(abs(sqrt(b**2 + 1) + b)) - log(abs(sqrt(a**2 + 1) + a))


def f(x):
    return 1/sqrt(x**2 + 1)


def R(b, a, s):
    return abs(naive(b, a) - s)


def sol(b, a, N):
    h = (b-a) / N

    s = 0.5 * f(0) + 0.5 * f(1)

    for i in range(2, N):
        xi = a + i * h
        s += f(xi)

    s *= h
    r = R(b, a, s)
    print(f"{s:.15f}", end=" ")
    print(f"{r:.15f}")


sol(1, 0, 10)
sol(1, 0, 100)
sol(1, 0, 1000)
sol(1, 0, 10000)
print(naive(0, 1))
