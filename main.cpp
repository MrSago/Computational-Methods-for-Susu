
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <ranges>
#include <vector>

using ld = long double;
using Matrix = std::vector<std::vector<ld>>;

constexpr ld EPS = 5e-4L;
constexpr int WEIGHT = 8;

Matrix GetMatrixFile(const char filename[]) {
    std::ifstream fin(filename);

    size_t n;
    fin >> n;

    Matrix matrix(n, std::vector<ld>(n + 1));
    std::ranges::for_each(matrix, [&fin](auto& vec) {
        std::ranges::for_each(vec, [&fin](auto& x) {
            fin >> x;
        });
    });

    return matrix;
}

void PrintMatrix(Matrix& matrix) {
    for (size_t i : std::views::iota(1ULL, matrix.size() + 1)) {
        std::string xi = std::string("x") + std::to_string(i);
        std::cout << std::setw(WEIGHT) << xi << ' ';
    }
    std::cout << std::setw(WEIGHT) << 'C' << std::endl;

    std::ranges::for_each(matrix, [](auto& vec) {
        std::ranges::for_each(vec, [](auto& x) {
            std::cout << std::setw(WEIGHT) << std::setprecision(4) << x << ' ';
        });
        std::cout << std::endl;
    });
    std::cout << std::endl;
}

template <typename T>
void PrintVector(std::vector<T>& vec) {
    std::ranges::for_each(vec, [](T& x) {
        std::cout << std::setprecision(10) << std::fixed << x << ' ';
    });
    std::cout << std::endl;
    std::cout.unsetf(std::ios_base::fixed);
};

Matrix PrepareMatrix(Matrix& src) {
    Matrix ret = src;

    for (size_t i : std::views::iota(0ULL, ret.size())) {
        ld x = -ret[i][i];
        ret[i][i] = 0;
        for (size_t j : std::views::iota(0ULL, ret[i].size())) {
            if (i != j) {
                ret[i][j] /= -x;
            }
        }
    }

    auto get_abs = [](auto& x) { return std::abs(x); };
    auto del_ten = [](auto& x) { x /= 10; };

    for (auto& vec : ret) {
        auto it = vec | std::views::transform(get_abs);
        ld mx = std::accumulate(it.begin(), it.end() - 1, 0.0L);
        while (mx > 1) {
            std::ranges::for_each(vec, del_ten);
            mx = std::accumulate(it.begin(), it.end() - 1, 0.0L);
        }
    }

    return ret;
}

size_t CountIterations(Matrix& matrix) {
    auto get_abs = [](auto& x) { return std::abs(x); };

    ld B = 0;
    for (auto& vec : matrix) {
        auto it = vec | std::views::transform(get_abs);
        B = std::max(B, std::accumulate(it.begin(), it.end() - 1, 0.0L));
    }

    ld C = 0;
    for (size_t i : std::views::iota(0ULL, matrix.size())) {
        C = std::max(C, matrix[i].back());
    }

    return static_cast<size_t>(
        std::ceil(std::log2l(EPS * (1 - B) / C) / std::log2l(B) - 1)
    );
}

std::vector<ld> IterationMethod(Matrix& matrix) {
    std::vector<ld> res(matrix.size());
    for (size_t i : std::views::iota(0ULL, res.size())) {
        res[i] = matrix[i].back();
    }

    size_t k = CountIterations(matrix);
    std::cout << "k = " << k << std::endl;

    std::cout << "i | result" << std::endl;
    std::cout << "0 | ";
    PrintVector(res);
    
    for (size_t i : std::views::iota(1ULL, k + 1)) {
        std::vector<ld> new_res(res.size());
        for (size_t j : std::views::iota(0ULL, res.size())) {
            new_res[j] = matrix[j].back();
            for (size_t u : std::views::iota(0ULL, res.size())) {
                new_res[j] -= res[u] * matrix[j][u];
            }
        }
        res = std::move(new_res);
        std::cout << i << " | ";
        PrintVector(res);
    }
    std::cout << std::endl;

    return res;
}

void CheckAnswer(Matrix& matrix, std::vector<ld>& vec) {
    std::cout << "Check answer:" << std::endl
              << "i |" << std::setw(11)
              << "A |" << std::setw(9)
              << "C" << std::endl;

    for (size_t i : std::views::iota(0ULL, vec.size())) {
        ld res = 0;
        for (size_t j : std::views::iota(0ULL, vec.size())) {
            res += matrix[i][j] * vec[j];
        }
        std::cout << i + 1 << " | "
                  << std::setw(WEIGHT) << res << " | "
                  << std::setw(WEIGHT) << matrix[i].back() << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    freopen("result.txt", "w", stdout);

    Matrix source_matrix = GetMatrixFile("prepared.txt");
    PrintMatrix(source_matrix);

    Matrix prepared_matrix = PrepareMatrix(source_matrix);
    PrintMatrix(prepared_matrix);

    std::vector<ld> ans = IterationMethod(prepared_matrix);

    std::cout << "Answer:" << std::endl;
    PrintVector(ans);
    std::cout << std::endl;

    CheckAnswer(source_matrix, ans);

    return 0;
}
