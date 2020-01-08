#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::string input;
    std::cin >> input;

    const int width = 25;
    const int height = 6;
    const int size = width * height;

    std::vector<std::string> layers;
    for (int i = 0; i < input.size() / size; i++) {
        int cur = i * size;
        layers.push_back(input.substr(cur, size));
    }

    int min = size;
    int res = -1;
    for (int i = 0; i < layers.size(); i++) {
        int occ = std::count(layers[i].begin(), layers[i].end(), '0');
        if (occ < min) {
            min = occ;
            res = i;
        }
    }

    int prod = std::count(layers[res].begin(), layers[res].end(), '1') * std::count(layers[res].begin(), layers[res].end(), '2');
    printf("%d\n", prod);

    std::vector<char> img(size);
    std::fill(img.begin(), img.end(), '2');
    for (const auto& layer : layers) {
        for (int i = 0; i < size; i++) {
            if (img[i] == '2') {
                switch (layer[i])
                {
                    case '0':
                        img[i] = ' ';
                        break;
                    case '1':
                        img[i] = 'x';
                        break;
                }
            }
        }
    }

    std::string image(img.data());

    for (int i = 0; i < height; i++) {
        int cur = i * width;
        printf("%s\n", image.substr(cur, width).c_str());
    }
}