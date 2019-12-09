#include <stdio.h>

int part1(int * tape) {
    int pos = 0;
    while (tape[pos] != 99) {
        int i = tape[pos+1];
        int j = tape[pos+2];
        int k = tape[pos+3];
        if (tape[pos] == 1) {
            int sum = tape[i] + tape[j];
            tape[k] = sum;
            //printf("%d should be %d + %d = %d\n", tape[k], tape[i], tape[j], sum);
            pos += 4;
        } else if (tape[pos] == 2) {
            int prod = tape[i] * tape[j];
            tape[k] = prod;
            //printf("%d should be %d * %d = %d\n", tape[k], tape[i], tape[j], prod);
            pos += 4;
        } else {
            printf("error\n");
            return -1;
        }
        //printf("%d\n", tape[0]);
    }

    return tape[0];
}

int main() {
    int tape[149];
    for (int i = 0; i < 149; i++) {
        scanf("%d,", tape+i);
    }

    printf("%d\n", part1(tape));
}