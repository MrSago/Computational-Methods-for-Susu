
from math import log, log10


def f(x, y):
    return x + 3*(log10(x))**2 - y


def fx(x, y):
    return 1 + 6 * log(x) / (x * log(10)**2)


def fy(x, y):
    return -1


def g(x, y):
    return 2*x**2 - x*y - 5*x + 1


def gx(x, y):
    return 4*x - y - 5


def gy(x, y):
    return -x


def determinant(a, b, c, d):
    """|a c|
       |b d|
    """
    return a*d - b*c


def newton(a, b, e=0.0001):
    x = [a]
    y = [b]

    while True:
        xn, yn = x[-1], y[-1]
        fr, fxr, fyr = f(xn, yn), fx(xn, yn), fy(xn, yn)
        gr, gxr, gyr = g(xn, yn), gx(xn, yn), gy(xn, yn)
        A = determinant(fr, gr, fyr, gyr)
        B = determinant(fxr, gxr, fr, gr)
        J = determinant(fxr, gxr, fyr, gyr)

        if (J == 0.0):
            print("Error. J == 0")
            x.append(xn - A/1)
            y.append(yn - B/1)
            continue
        x.append(xn - A/J)
        y.append(yn - B/J)
        if abs(x[-1] - xn) < e and abs(y[-1] - yn) < e:
            break

    return x[-1], y[-1]


print(newton(0.1, 2))
print(newton(7, 9))
