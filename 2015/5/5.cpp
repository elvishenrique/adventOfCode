#include <stdio.h>
#include <string.h>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

bool checkVowels(char* name, int n)
{
    unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u'};
    int v = 0;
    for (int i = 0; i < n; i++)
    {
        if (vowels.contains(name[i]))
            v++;

        if (v == 3)
            return true;
    }

    return v >= 3;
}

bool twice(char* name, int n)
{
    for (int i = 1; i < n; i++)
    {
        if (name[i] == name[i - 1])
            return true;
    }

    return false;
}

bool allowed(char* name, int n)
{
    unordered_map<char, char> bad = {{'a', 'b'}, {'c', 'd'}, {'p', 'q'}, {'x', 'y'}};
    for (int i = 0; i < n - 1; i++)
    {
        if (bad.contains(name[i]) && name[i + 1] == bad[name[i]])
            return false;
    }

    return true;
}

bool twice2(char* name, int n)
{
    unordered_map<string, int> pairs;
    for (int i = 0; i < n - 1; i++)
    {
        string pair;
        pair += name[i];
        pair += name[i + 1];
        if (pairs.contains(pair))
        {
            if (pairs[pair] + 1 < i)
                return true;
        }
        else
        {
            pairs[pair] = i;
        }
    }

    return false;
}

bool between(char* name, int n)
{
    for (int i = 0; i < n - 2; i++)
    {
        if (name[i] == name[i + 2])
            return true;
    }

    return false;
}

bool nice(char* name, int n)
{
    return checkVowels(name, n) && twice(name, n) && allowed(name, n);
}

bool nice2(char* name, int n)
{
    return twice2(name, n) && between(name, n);
}

int main()
{
    char name[1000];
    int n = 0, n2 = 0;
    for (int i = 0; i < 1000; i++)
    {
        scanf("%s", name);
        int len = strlen(name);
        if (nice(name, len))
            n++;

        if (nice2(name, len))
            n2++;
    }

    printf("%d\n%d\n", n, n2);
}