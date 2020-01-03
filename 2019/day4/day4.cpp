#include <stdio.h>

bool verify(int n) {
    int i = 100000;
    bool duplicate = false;
    while (i > 1) {
        int cur = (n/i) % 10;
        int nex = (n*10/i) % 10;

        if (cur > nex)
            return false;

        if (cur == nex)
            duplicate = true;

        i /= 10;
    }

    return duplicate;
}

bool verify2(int n) {
    int i = 100000, buckets[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    while (i > 0) {
        int cur = (n/i) % 10;
        buckets[cur]++;
        i /= 10;
    }

    for (int j = 0; j < 10; j++) {
        if (buckets[j] == 2)
            return true;
    }

    return false;
}

int main() {
    int start = 240920;
    int end = 789857;
    int accept = 0, acc = 0;
    for (int i = start; i <= end; i++) {
        if (verify(i)) {
            accept++;
            if (verify2(i)) {
                acc++;
            }
        }
    }

    printf("%d\n", accept);
    printf("%d\n", acc);
}