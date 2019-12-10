#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

struct point {
    int x;
    int y;

    point() = default;
    point(int a, int b) : x(a), y(b) {}

    point move(std::string direction) {
        switch (direction[0]) {
            case 'U':
                y += std::stoi(direction.substr(1));
            case 'D':
                y -= std::stoi(direction.substr(1));
            case 'L':
                x -= std::stoi(direction.substr(1));
            case 'R':
                x += std::stoi(direction.substr(1));
        }

        return *this;
    }
};

int dist (const point& p) {
    return p.x + p.y;
}

struct segment {
    point a;
    point b;

    segment(point c, point d) : a(c) , b(d) {}
};

bool isHorizontal(segment r) {
    return r.a.x == r.b.x;
}

bool intersect(segment r, segment s, point* p) {
    if (isHorizontal(r) == isHorizontal(s))
        return false;

    if (isHorizontal(r)) {
        if (s.a.y <= std::max(r.a.y, r.b.y) && s.a.y >= std::min(r.a.y, r.b.y)) {
            if (p != nullptr)
                *p = point(r.a.x, s.a.y);

            return true;
        }

        return false;
    }

    if (s.a.x <= std::max(r.a.x, r.b.x) && s.a.x >= std::min(r.a.x, r.b.x)) {
        if (p != nullptr)
            *p = point(s.a.x, r.a.y);

        return true;
    }

    return false;
}

void print(int value) {
    std::cout << value << "\n";
}

int main() {
    // std::string str;

    // std::cin >> str;
    // std::cout << str << "\n";

    // std::cin >> str;
    // std::cout << str << "\n";

    std::vector<segment> wire1;
    std::vector<segment> wire2;
    point curpos(0,0);

    std::string line;

    std::cin >> line;
    while (line[0] != 's') {
        wire1.emplace_back(curpos, curpos.move(line));
        std::cin >> line;
    }

    curpos = point(0,0);
    std::cin >> line;
    while (line[0] != 's') {
        wire2.emplace_back(curpos, curpos.move(line));
        std::cin >> line;
    }

    std::vector<point> inter;
    for (const auto& seg1 : wire1) {
        for (const auto& seg2 : wire2) {
            point p;
            print(seg2.a.x);
            if (intersect(seg1, seg2, &p))
                inter.push_back(p);
        }
    }

    std::vector<point>::iterator it = std::min_element(inter.begin(), inter.end(), [] (const point& p, const point& q) { return dist(p) < dist(q); });
    print(dist(*it));
}