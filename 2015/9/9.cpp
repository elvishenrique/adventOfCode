#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

unordered_map<string, int> cityIds;
int distances[8][8];
int id = 0;

int pathSize(const vector<int>& perm)
{
    int result = 0;
    for (int i = 0; i < perm.size() - 1; i++)
    {
        result += distances[perm[i]][perm[i + 1]];
    }

    return result;
}

void parse(const string& line)
{
    string::size_type toPos = line.find(" to ");
    string::size_type eqPos = line.find(" = ");
    string from = line.substr(0, toPos);
    string to = line.substr(toPos + 4, eqPos - toPos - 4);
    int distance = stoi(line.substr(eqPos + 3));

    if (!cityIds.contains(from))
        cityIds[from] = id++;

    if (!cityIds.contains(to))
        cityIds[to] = id++;

    distances[cityIds[from]][cityIds[to]] = distance;
    distances[cityIds[to]][cityIds[from]] = distance;
}

int main()
{
    for (int i = 0; i < 28; i++)
    {
        string line;
        getline(cin, line);
        parse(line);
    }

    vector<int> permutation = {0, 1, 2, 3, 4, 5, 6, 7};
    vector<int> shortestPath(8);
    int shortest = 10000;
    int longest = 0;
    do
    {
        int path = pathSize(permutation);
        if (path < shortest)
            shortest = path;

        if (path > longest)
            longest = path;
    } while (next_permutation(permutation.begin(), permutation.end()));

    printf("%d\n%d\n", shortest, longest);
}