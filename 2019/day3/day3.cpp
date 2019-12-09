#include <stdio.h>
#include <ctype.h>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

std::vector<std::string> split(std::string str, char delim) {
    std::vector<std::string> result;
    auto start = 0U;
    auto end = str.find(delim);
    while (end != std::string::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find(delim);
    }

    result.push_back(str.substr(start, end));
    return result;
}

int main() {
    std::vector<std::string> wire1;
    std::vector<std::string> wire2;
    std::unordered_set<std::pair<int, int>> points;

    char * w;
    scanf("%s", w);
    wire1 = split(w, ',');
    scanf("%s", w);
    wire2 = split(w, ',');

    printf("%s", wire1[0]);
    printf("%s", wire2[0]);
}