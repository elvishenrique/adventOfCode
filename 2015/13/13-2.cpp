#include <iostream>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

unordered_map<string, int> personIds;
int happiness[9][9];
int id = 0;

int totalHappiness(const vector<int>& perm)
{
    int result = 0, n = perm.size();
    for (int i = 0; i < n; i++)
    {
        result += happiness[perm[i]][perm[(i + 1) % n]] + happiness[perm[(i + 1) % n]][perm[i]];
    }

    return result;
}

void parse(const string& line)
{
    string::size_type wouldPos = line.find(" would ");
    string::size_type gainPos = line.find(" gain ");
    string::size_type losePos = line.find(" lose ");
    string::size_type happyPos = line.find(" happiness ");
    string::size_type nextPos = line.find(" next to ");
    string::size_type dotPos = line.find(".");
    string source = line.substr(0, wouldPos);
    int points;
    if (gainPos != string::npos)
    {
        points = stoi(line.substr(gainPos + 6, happyPos - gainPos - 6));
    }
    else
    {
        points = -1 * stoi(line.substr(losePos + 6, happyPos - losePos - 6));
    }
    string target = line.substr(nextPos + 9, dotPos - nextPos - 9);

    if (!personIds.contains(source))
        personIds[source] = id++;

    if (!personIds.contains(target))
        personIds[target] = id++;

    happiness[personIds[source]][personIds[target]] = points;
}

int main()
{
    for (int i = 0; i < 56; i++)
    {
        string line;
        getline(cin, line);
        parse(line);
    }

    for (int i = 0; i < 8; i++)
    {
        happiness[i][8] = 0;
        happiness[8][i] = 0;
    }

    vector<int> permutation = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
    int max = -100000;
    do
    {
        int happy = totalHappiness(permutation);
        if (happy > max)
            max = happy;
    } while (next_permutation(permutation.begin(), permutation.end()));

    printf("%d\n", max);
}
