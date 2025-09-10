#include <stdio.h>
#include <string.h>

using namespace std;

int main()
{
    int pad1[3][3] = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
    int part1[5];
    int x1 = 1, y1 = 1;

    char pad2[5][5] = { { ' ', ' ', '1', ' ', ' ' }, { ' ', '2', '3', '4', ' ' }, { '5', '6', '7', '8', '9' }, { ' ', 'A', 'B', 'C', ' ' }, { ' ', ' ', 'D', ' ', ' ' } };
    char part2[5];
    int x2 = 2, y2 = 0;
    for (int i = 0; i < 5; i++)
    {
        char instruction[600];
        fgets(instruction, sizeof instruction, stdin);
        int n = strlen(instruction);
        for (int j = 0; j < n; j++)
        {
            char direction = instruction[j];
            if (direction == 'U')
            {
                if (x1 > 0) x1--;
                if (x2 > 0 && pad2[x2 - 1][y2] != ' ') x2--;
            }
            else if (direction == 'D')
            {
                if (x1 < 2) x1++;
                if (x2 < 4 && pad2[x2 + 1][y2] != ' ') x2++;
            }
            else if (direction == 'L')
            {
                if (y1 > 0) y1--;
                if (y2 > 0 && pad2[x2][y2 - 1] != ' ') y2--;
            }
            else if (direction == 'R')
            {
                if (y1 < 2) y1++;
                if (y2 < 4 && pad2[x2][y2 + 1] != ' ') y2++;
            }
        }

        part1[i] = pad1[x1][y1];
        part2[i] = pad2[x2][y2];
    }

    printf("part 1: ");
    for (int i = 0; i < 5; i++)
    {
        printf("%d", part1[i]);
    }

    printf("\npart 2: ");
    for (int i = 0; i < 5; i++)
    {
        printf("%c", part2[i]);
    }

    printf("\n");
}