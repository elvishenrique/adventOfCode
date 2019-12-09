#include <stdio.h>

int main() {
    int fuel = 0;
    for (int i = 0; i < 100; i++) {
        int mass;
        scanf("%d", &mass);
        int j = mass/3 - 2;
        int module = 0;
        while (j > 0) {
            module += j;
            j = j/3 -2;
        }
        fuel += module;
    }

    printf("%d\n", fuel);
}