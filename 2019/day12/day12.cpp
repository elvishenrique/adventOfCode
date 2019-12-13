#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <vector>

int sign(int x) {
    if (x == 0) return 0;
    return abs(x) / x;
}

struct vec {
    int x;
    int y;
    int z;

    vec(int a, int b, int c) : x(a), y(b), z(c) {}

    int norm() const {
        return abs(x) + abs(y) + abs(z);
    }

    void print() const {
        printf("(%d, %d, %d)", x, y, z);
    }

    vec& operator+=(vec& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }
};

struct body {
    vec pos;
    vec vel;
    vec g;

    body(vec start) : pos(start), vel(0, 0, 0), g(0, 0, 0) {}

    void applyg() {
        vel += g;
    }

    void applyvel() {
        pos += vel;
    }

    void update() {
        applyg();
        applyvel();
    }

    int pot() const {
        return pos.norm();
    }

    int kin() const {
        return vel.norm();
    }

    int energy() const {
        return pot() * kin();
    }

    void print() const {
        printf("pos: ");
        pos.print();
        printf(", vel: ");
        vel.print();
        printf(", g: ");
        g.print();
    }
};

void cleang(std::vector<body>& univ) {
    for (auto& moon : univ) {
        moon.g = vec(0, 0, 0);
    }
}

void calculateg(std::vector<body>& univ) {
    cleang(univ);
    for (int i = 0; i < univ.size(); i++) {
        for (int j = i + 1; j < univ.size(); j++) {
            vec grav = vec(sign(univ[j].pos.x - univ[i].pos.x), sign(univ[j].pos.y - univ[i].pos.y), sign(univ[j].pos.z - univ[i].pos.z));
            univ[i].g += grav;
            grav = vec(sign(univ[i].pos.x - univ[j].pos.x), sign(univ[i].pos.y - univ[j].pos.y), sign(univ[i].pos.z - univ[j].pos.z));
            univ[j].g += grav;
            // univ[i].g.y += sign(univ[j].pos.y - univ[i].pos.y);
            // univ[i].g.z += sign(univ[j].pos.z - univ[i].pos.z);

            // univ[j].g.x += sign(univ[i].pos.x - univ[j].pos.x);
            // univ[j].g.y += sign(univ[i].pos.y - univ[j].pos.y);
            // univ[j].g.z += sign(univ[i].pos.z - univ[j].pos.z);
        }
    }
}

void update(std::vector<body>& univ) {
    calculateg(univ);
    for (auto& moon : univ) {
        moon.update();
    }
}

int totalenergy(const std::vector<body>& univ) {
    int res = 0;
    for (const auto& moon : univ) {
        res += moon.energy();
    }

    return res;
}

void print(const std::vector<body>& univ) {
    for (const auto& moon : univ) {
        moon.print();
        printf("\n");
    }
}

int main() {
    std::vector<body> universe;
    for (int i = 0; i < 4; i++) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        universe.emplace_back(vec(x, y, z));
    }

    unsigned long long steps = 0;
    printf("step 0:\n");
    print(universe);
    //for (int i = 0; i < 2772; i++) {
    do {
        update(universe);

        if (steps % 10000000 == 0) {
            printf("step %u:\n", steps + 1);
            print(universe);
        }

        steps++;
    } while (totalenergy(universe) != 0);

    printf("step %u:\n", steps);
    print(universe);
}