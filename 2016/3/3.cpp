#include <algorithm>
#include <stdio.h>
#include <vector>

using namespace std;

int main()
{
    constexpr int n = 1992 * 3;
    int input1[n], input2[n];
    for (int i = 0; i < 1992; i++)
    {
        int a, b, c;
        scanf("%d", &a);
        scanf("%d", &b);
        scanf("%d", &c);
        input1[3 * i] = a;
        input1[3 * i + 1] = b;
        input1[3 * i + 2] = c;
        input2[i] = a;
        input2[1992 + i] = b;
        input2[1992 * 2 + i] = c;
    }

    int part1 = 0, part2 = 0;
    for (int i = 0; i < 1992; i++)
    {
        vector<int> tri1({ input1[3 * i], input1[3 * i + 1], input1[3 * i + 2] });
        sort(tri1.begin(), tri1.end());
        if (tri1[0] + tri1[1] > tri1[2]) part1++;

        vector<int> tri2({ input2[3 * i], input2[3 * i + 1], input2[3 * i + 2] });
        sort(tri2.begin(), tri2.end());
        if (tri2[0] + tri2[1] > tri2[2]) part2++;
    }

    printf("part1: %d\npart2: %d\n", part1, part2);
}