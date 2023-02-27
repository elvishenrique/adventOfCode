#include <stdio.h>

int live_neighbors(bool field[100][100], int i, int j)
{
    int result = 0;
    for (int k = i - 1; k <= i + 1; k++)
    {
        if (k >= 0 && k < 100)
        {
            for (int l = j - 1; l <= j + 1; l++)
            {
                if (l >= 0 && l < 100)
                {
                    if (field[k][l])
                        result++;
                }
            }
        }
    }

    if (field[i][j])
        result--;

    return result;
}

void update(bool field[100][100])
{
    bool result[100][100];
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            int neigh = live_neighbors(field, i, j);
            if (field[i][j])
            {
                result[i][j] = (neigh == 2 || neigh == 3);
            }
            else
            {
                result[i][j] = (neigh == 3);
            }
        }
    }

    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            field[i][j] = result[i][j];
        }
    }

    field[0][0] = true;
    field[0][99] = true;
    field[99][0] = true;
    field[99][99] = true;
}

int lights_on(bool field[100][100])
{
    int result = 0;
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            if (field[i][j])
                result++;
        }
    }

    return result;
}

int main()
{
    bool field[100][100];
    for (int i = 0; i < 100; i++)
    {
        char line[100];
        scanf("%s", line);
        for (int j = 0; j < 100; j++)
        {
            field[i][j] = (line[j] == '#');
        }
    }

    for (int i = 0; i < 100; i++)
    {
        update(field);
    }

    printf("%d\n", lights_on(field));
}