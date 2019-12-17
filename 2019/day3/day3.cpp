#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
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
                break;
            case 'D':
                y -= std::stoi(direction.substr(1));
                break;
            case 'L':
                x -= std::stoi(direction.substr(1));
                break;
            case 'R':
                x += std::stoi(direction.substr(1));
                break;
        }

        return point(x,y);
    }
};

int dist (const point& p) {
    return std::abs(p.x) + std::abs(p.y);
}

bool isOrigin(point p) {
    return p.x == 0 && p.y == 0;
}

struct segment {
    point a;
    point b;

    segment(point c, point d) : a(c) , b(d) {}
};

bool isHorizontal(segment r) {
    return r.a.y == r.b.y;
}

bool intersect(segment r, segment s, point* p) {
    if (isHorizontal(r) == isHorizontal(s))
        return false;

    if (isHorizontal(r)) {
        if (s.a.x <= std::max(r.a.x, r.b.x)
            && s.a.x >= std::min(r.a.x, r.b.x)
            && r.a.y <= std::max(s.a.y, s.b.y)
            && r.a.y >= std::min(s.a.y, s.b.y)) {
            if (p != nullptr)
                *p = point(s.a.x, r.a.y);

            return true;
        }

        return false;
    }

    if (s.a.y <= std::max(r.a.y, r.b.y)
        && s.a.y >= std::min(r.a.y, r.b.y)
        && r.a.x <= std::max(s.a.x, s.b.x)
        && r.a.x >= std::min(s.a.x, s.b.x)) {
        if (p != nullptr)
            *p = point(r.a.x, s.a.y);

        return true;
    }

    return false;
}

void print(int value) {
    std::cout << value << "\n";
}

void print(point p) {
    std::printf("(%d, %d)\n", p.x, p.y);
}

int main() {
    // std::string str;

    // std::cin >> str;
    // std::cout << str << "\n";

    // std::cin >> str;
    // std::cout << str << "\n";

    std::vector<segment> wire1;
    std::vector<segment> wire2;
    //bool debug = true;
    point curpos(0,0);

    std::string line;

    std::cin >> line;
    while (line[0] != 's') {
        point a = curpos;
        point b = curpos.move(line);
        wire1.emplace_back(a, b);
        std::cin >> line;
    }

    curpos = point(0,0);
    std::cin >> line;
    while (line[0] != 's') {
        point a = curpos;
        point b = curpos.move(line);
        wire2.emplace_back(a, b);
        std::cin >> line;
    }

    std::vector<point> inter;
    for (const auto& seg1 : wire1) {
        for (const auto& seg2 : wire2) {
            point p;
            if (intersect(seg1, seg2, &p)) {
                if (!isOrigin(p))
                    inter.push_back(p);
                if (dist(p) == 374) {
                    print(seg1.a);
                    print(seg1.b);
                    print(seg2.a);
                    print(seg2.b);
                    //print(p);
                }
            }
        }
    }

    if (inter.size() > 0) {
        std::vector<point>::iterator it = std::min_element(inter.begin(), inter.end(), [] (const point& p, const point& q) { return dist(p) < dist(q); });
        print(dist(*it));
        print(*it);
    } else {
        printf("error\n");
    }
}