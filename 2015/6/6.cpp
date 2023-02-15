#include <iostream>
#include <string>

using namespace std;

class Lights
{
public:
    Lights()
    {
        for (int i = 0; i < 1000; i++)
        {
            for (int j = 0; j < 1000; j++)
            {
                grid[i][j] = false;
            }
        }
    }

    int lit()
    {
        int n = 0;
        for (int i = 0; i < 1000; i++)
        {
            for (int j = 0; j < 1000; j++)
            {
                if (grid[i][j])
                    n++;
            }
        }

        return n;
    }

    void turnOn(int a, int b, int x, int y)
    {
        if (a > x)
        {
            int temp = x;
            x = a;
            a = temp;
        }

        if (b > y)
        {
            int temp = y;
            y = b;
            b = temp;
        }

        for (int i = a; i < x + 1; i++)
        {
            for (int j = b; j < y + 1; j++)
            {
                grid[i][j] = true;
            }
        }
    }

    void turnOff(int a, int b, int x, int y)
    {
        if (a > x)
        {
            int temp = x;
            x = a;
            a = temp;
        }

        if (b > y)
        {
            int temp = y;
            y = b;
            b = temp;
        }

        for (int i = a; i < x + 1; i++)
        {
            for (int j = b; j < y + 1; j++)
            {
                grid[i][j] = false;
            }
        }
    }

    void toggle(int a, int b, int x, int y)
    {
        if (a > x)
        {
            int temp = x;
            x = a;
            a = temp;
        }

        if (b > y)
        {
            int temp = y;
            y = b;
            b = temp;
        }

        for (int i = a; i < x + 1; i++)
        {
            for (int j = b; j < y + 1; j++)
            {
                grid[i][j] = !grid[i][j];
            }
        }
    }

    bool grid[1000][1000];
};

class Lights2
{
public:
    Lights2()
    {
        for (int i = 0; i < 1000; i++)
        {
            for (int j = 0; j < 1000; j++)
            {
                grid[i][j] = 0;
            }
        }
    }

    int brightness()
    {
        int n = 0;
        for (int i = 0; i < 1000; i++)
        {
            for (int j = 0; j < 1000; j++)
            {
                n += grid[i][j];
            }
        }

        return n;
    }

    void turnOn(int a, int b, int x, int y)
    {
        if (a > x)
        {
            int temp = x;
            x = a;
            a = temp;
        }

        if (b > y)
        {
            int temp = y;
            y = b;
            b = temp;
        }

        for (int i = a; i < x + 1; i++)
        {
            for (int j = b; j < y + 1; j++)
            {
                grid[i][j]++;
            }
        }
    }

    void turnOff(int a, int b, int x, int y)
    {
        if (a > x)
        {
            int temp = x;
            x = a;
            a = temp;
        }

        if (b > y)
        {
            int temp = y;
            y = b;
            b = temp;
        }

        for (int i = a; i < x + 1; i++)
        {
            for (int j = b; j < y + 1; j++)
            {
                if (grid[i][j] > 0)
                    grid[i][j]--;
            }
        }
    }

    void toggle(int a, int b, int x, int y)
    {
        if (a > x)
        {
            int temp = x;
            x = a;
            a = temp;
        }

        if (b > y)
        {
            int temp = y;
            y = b;
            b = temp;
        }

        for (int i = a; i < x + 1; i++)
        {
            for (int j = b; j < y + 1; j++)
            {
                grid[i][j] += 2;
            }
        }
    }

    int grid[1000][1000];
};

void getArgs(const string& instruction, int* a, int* b, int* x, int* y, int* inst)
{
    int start;
    if (instruction.starts_with("turn on"))
    {
        start = 8;
        *inst = 0;
    }
    else if (instruction.starts_with("turn off"))
    {
        start = 9;
        *inst = 1;
    }
    else
    {
        start = 7;
        *inst = 2;
    }

    string first = instruction.substr(start, instruction.find(" through") - start);
    string::size_type comma = first.find(',');
    *a = stoi(first.substr(0, comma));
    *b = stoi(first.substr(comma + 1));

    string second = instruction.substr(instruction.find("through ") + 8);
    comma = second.find(',');
    *x = stoi(second.substr(0, comma));
    *y = stoi(second.substr(comma + 1));
}

int main()
{
    Lights lights;
    Lights2 lights2;

    for (int i = 0; i < 300; i++)
    {
        string instruction;
        getline(cin, instruction);

        int a, b, x, y, inst;
        getArgs(instruction, &a, &b, &x, &y, &inst);

        switch(inst)
        {
        case 0:
            lights.turnOn(a, b, x, y);
            lights2.turnOn(a, b, x, y);
            break;
        case 1:
            lights.turnOff(a, b, x, y);
            lights2.turnOff(a, b, x, y);
            break;
        case 2:
            lights.toggle(a, b, x, y);
            lights2.toggle(a, b, x, y);
            break;
        }
    }

    printf("%d\n%d\n", lights.lit(), lights2.brightness());
}