
#include <cmath>
#include <iomanip>
#include <iostream>

using ld = long double;

constexpr ld EPS = 1E-3L;


ld f(ld x) {
    return std::atan(3 * x);
}

ld IterationMethod(ld start) {
    ld x0, x;
    x0 = x = start;

    do {
        x0 = x;
        x = f(x0);
    } while (std::abs(x - x0) > EPS);

    return x;
}

int main() {
    constexpr ld s1 = 0.0L;
    constexpr ld s2 = -1.0L;
    constexpr ld s3 = 1.0L;

    ld x1, x2, x3;
    x1 = IterationMethod(s1);
    x2 = IterationMethod(s2);
    x3 = IterationMethod(s3);

    std::cout << std::setprecision(4);
    std::cout << "x = arctg(x)\n\n";

    std::cout << "s1 = " << s1 << '\n';
    std::cout << "x1 = " << x1 << "\n\n";

    std::cout << "s2 = " << s2 << '\n';
    std::cout << "x2 = " << x2 << "\n\n";

    std::cout << "s3 = " << s3 << '\n';
    std::cout << "x3 = " << x3 << "\n\n";

    return 0;
}
