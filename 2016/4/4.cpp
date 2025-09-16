#include <map>
#include <stdio.h>
#include <string>
#include <string.h>

using namespace std;

bool isReal(char* room, char* checksum)
{
    map<char, int> counts;
    int n = strlen(room), m = strlen(checksum);
    for (int i = 0; i < n; i++)
    {
        if (room[i] == '-')
            continue;

        if (counts.find(room[i]) == counts.end())
            counts[room[i]] = 1;
        else
            counts[room[i]]++;
    }

    for (int i = 1; i < m; i++)
    {
        if (counts.find(checksum[i]) == counts.end())
            return false;

        if (counts[checksum[i]] > counts[checksum[i - 1]])
            return false;

        if (counts[checksum[i]] == counts[checksum[i - 1]] && checksum[i] < checksum[i - 1])
            return false;
    }

    return true;
}

char shiftLetter(char c, int n)
{
    int p = c - 'a';
    p = (p + n) % 26;
    return 'a' + p;
}

char* decrypt(char* name, int id)
{
    int n = strlen(name);
    char* result = (char*) malloc(n * sizeof(char));
    for (int i = 0; i < n - 1; i++)
    {
        if (name[i] == '-')
            result[i] = '-';
        else
            result[i] = shiftLetter(name[i], id);
    }

    result[n - 1] = 0;

    return result;
}

int main()
{
    char name[100];
    int id, sum = 0, n = 953;
    char checksum[26];

    for (int i = 0; i < n; i++)
    {
        scanf("%[a-z\\-]%d[%[a-z]]\n", name, &id, checksum);
        if (isReal(name, checksum))
        {
            printf("name: %s\tid: %d\n", decrypt(name, id), id);
            sum += id;
        }
    }

    printf("%d\n", sum);
}