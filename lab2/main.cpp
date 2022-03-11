
#include <iostream>
#include <cmath>

double f(double x) {
    return std::atan(3 * x) - x;
}

double fp(double x) {
    return 1 / (1 + 9 * x * x) - 1;
}

int main() {
    const double eps = 0.001;

    double x;
    std::cin >> x;
    
    while (std::abs(f(x)) > eps) {
        x -= f(x) / fp(x);
    }

    std::cout << '\n' << x << '\n';

    return 0;
}
