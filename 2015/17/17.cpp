#include <algorithm>
#include <math.h>
#include <stdio.h>
#include <vector>

using namespace std;

int smallest(const vector<int>& containers, int start, int used, int size)
{
    if (start == containers.size())
        return start;

    if (containers[start] > size)
        return smallest(containers, start + 1, used, size);

    if (containers[start] == size)
        return used + 1;

    return min(smallest(containers, start + 1, used + 1, size - containers[start]), smallest(containers, start + 1, used, size));
}

int target_combinations(const vector<int>& containers, int start, int limit, int size)
{
    if (start == containers.size() || limit == 0)
        return 0;

    if (containers[start] > size && limit > 0)
        return target_combinations(containers, start + 1, limit, size);

    if (containers[start] == size && limit > 0)
        return 1 + target_combinations(containers, start + 1, limit, size);

    return target_combinations(containers, start + 1, limit - 1, size - containers[start]) + target_combinations(containers, start + 1, limit, size);
}

int combinations(const vector<int>& containers, int start, int size)
{
    if (start == containers.size())
        return 0;

    if (containers[start] > size)
        return combinations(containers, start + 1, size);

    if (containers[start] == size)
        return 1 + combinations(containers, start + 1, size);

    return combinations(containers, start + 1, size - containers[start]) + combinations(containers, start + 1, size);
}

int main()
{
    vector<int> containers;
    // for (int i = 0; i < 5; i++)
    for (int i = 0; i < 20; i++)
    {
        int cont;
        scanf("%d", &cont);
        containers.push_back(cont);
    }

    sort(containers.begin(), containers.end(), [](int a, int b)
    {
        return a > b;
    });

    // printf("%d\n", combinations(containers, 0, 25));
    // int i = smallest(containers, 0, 0, 25);
    // printf("%d\n", i);
    // printf("%d\n", target_combinations(containers, 0, i, 25));
    printf("%d\n", combinations(containers, 0, 150));
    int i = smallest(containers, 0, 0, 150);
    printf("%d\n", i);
    printf("%d\n", target_combinations(containers, 0, i, 150));
}