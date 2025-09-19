#include <stdio.h>
#include <string.h>

class Screen
{
public:
    bool m_screen[6][50];
    const int m_rows = 6;
    const int m_columns = 50;

    Screen()
    {
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 50; j++)
            {
                m_screen[i][j] = false;
            }
        }
    }

    void rect(int rows, int columns)
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                m_screen[i][j] = true;
            }
        }
    }

    void rotateRow(int row, int shift)
    {
        bool previous[m_columns];
        for (int i = 0; i < m_columns; i++)
        {
            previous[i] = m_screen[row][i];
        }

        for (int i = 0; i < m_columns; i++)
        {
            m_screen[row][i] = previous[(i - shift + m_columns) % m_columns];
        }
    }

    void rotateColumn(int column, int shift)
    {
        bool previous[m_rows];
        for (int i = 0; i < m_rows; i++)
        {
            previous[i] = m_screen[i][column];
        }

        for (int i = 0; i < m_rows; i++)
        {
            m_screen[i][column] = previous[(i - shift + m_rows) % m_rows];
        }
    }

    void print()
    {
        for (int i = 0; i < m_rows; i++)
        {
            for (int j = 0; j < m_columns; j++)
            {
                if (m_screen[i][j])
                {
                    printf("#");
                }
                else
                {
                    printf(".");
                }
            }
            printf("\n");
        }
    }
};

void readInstruction(Screen& screen)
{
    char instruction[7];
    scanf("%s", instruction);
    if (strcmp(instruction, "rect") == 0)
    {
        int rows, columns;
        scanf("%dx%d\n", &columns, &rows);
        screen.rect(rows, columns);
    }
    else if (strcmp(instruction, "rotate") == 0)
    {
        char direction[7];
        scanf("%s", direction);
        if (strcmp(direction, "row") == 0)
        {
            int row = 0, shift = 0;
            scanf(" y=%d by %d\n", &row, &shift);
            screen.rotateRow(row, shift);
        }
        else if (strcmp(direction, "column") == 0)
        {
            int column, shift;
            scanf(" x=%d by %d\n", &column, &shift);
            screen.rotateColumn(column, shift);
        }
    }
}

int main()
{
    Screen screen = Screen();
    for (int i = 0; i < 173; i++)
    {
        readInstruction(screen);
    }

    int lit = 0;
    for (int i = 0; i < screen.m_rows; i++)
    {
        for (int j = 0; j < screen.m_columns; j++)
        {
            if (screen.m_screen[i][j])
                lit++;
        }
    }

    printf("%d\n\n", lit);
    screen.print();
}