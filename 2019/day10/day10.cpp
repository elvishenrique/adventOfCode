#include <algorithm>
#include <complex>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

double pi = std::arg(std::complex(-1.0, 0.0));

int to_int(std::complex<int> z) {
    return 100 * z.real() + z.imag();
}

std::complex<int> to_complex(int i) {
    return std::complex(i / 100, i % 100);
}

std::complex<double> to_double(std::complex<int> z) {
    return std::complex((double) z.real(), (double) z.imag());
}

typedef std::unordered_map<int, std::vector<std::complex<int>>> starmap;

double angle(std::complex<int> src, std::complex<int> target) {
    std::complex<double> z = to_double(src) - to_double(target);
    if (std::arg(std::complex(-z.imag(), -z.real())) == -pi)
        return pi;

    return std::arg(std::complex(-z.imag(), -z.real()));
}

bool blocked(const starmap& asts, std::complex<int> src, std::complex<int> target) {
    // self blocked
    if (src == target)
        return true;

    std::complex<int> z = target - src;
    int div = std::gcd(z.real(), z.imag());
    for (std::complex<int> x = z / div; x != z; x += z / div) {
        if (asts.find(to_int(src + x)) != asts.end()) {
            return true;
        }
    }

    return false;
}

int main() {
    std::vector<std::string> input;
    for (int i = 0; i < 26; i++) {
        std::string line;
        std::cin >> line;
        input.push_back(line);
    }

    starmap asteroids;
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[i].size(); j++) {
            if (input[i][j] == '#') {
                asteroids[100 * j + i] = std::vector<std::complex<int>>();
            }
        }
    }

    for (const auto& ast : asteroids) {
        for (const auto& vis : asteroids) {
            if (!blocked(asteroids, to_complex(ast.first), to_complex(vis.first))) {
                asteroids[ast.first].push_back(to_complex(vis.first));
            }
        }
    }

    std::pair<int, std::vector<std::complex<int>>> vap = *(std::max_element(asteroids.begin(), asteroids.end(), [](const std::pair<int, std::vector<std::complex<int>>>& v1, const std::pair<int, std::vector<std::complex<int>>>& v2) {
        return v1.second.size() < v2.second.size();
    }));
    printf("%lu\n", vap.second.size());

    std::sort(vap.second.begin(), vap.second.end(), [vap](const std::complex<int>& z1, const std::complex<int>& z2) {
        return angle(to_complex(vap.first), z1) > angle(to_complex(vap.first), z2);
    });

    printf("%d\n", to_int(vap.second[199]));
}