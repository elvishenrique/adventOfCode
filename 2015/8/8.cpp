#include <iostream>
#include <string>

using namespace std;

int escaped(string line)
{
    int result = 2;

    for (int i = 1; i < line.size() - 1; i++)
    {
        if (line[i] == '\\')
        {
            if (line[i + 1] == 'x')
            {
                i += 3;
                result += 3;
            }
            else
            {
                i += 1;
                result += 1;
            }
        }
    }

    return result;
}

int nonscaped(string line)
{
    int result = 2;
    for (int i = 0; i < line.size(); i++)
    {
        if (line[i] == '"' || line[i] == '\\')
            result += 1;
    }

    return result;
}

int main()
{
    int skipped = 0;
    int added = 0;
    for (int i = 0; i < 300; i++)
    {
        string line;
        getline(cin, line);
        skipped += escaped(line);
        added += nonscaped(line);
    }

    printf("%d\n", skipped);
    printf("%d\n", added);
}