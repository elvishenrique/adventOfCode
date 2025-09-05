#include <algorithm>
#include <stdio.h>
#include <vector>

using namespace std;

void printGroup(vector<int> group, int number, int groupSum)
{
    printf("group %d: { ", number);
    for (int i = 0; i < group.size(); i++)
    {
        if (i > 0)
            printf(", ");

        printf("%d", group[i]);
    }

    printf(" }\tgroup sum: %d\n", groupSum);
}

unsigned long long quantumEntanglement(vector<int> group)
{
    unsigned long long product = 1;
    for (int weight : group)
    {
        product *= weight;
    }

    return product;
}

unsigned long long minEntanglement(vector<int> weights, int k, int desiredSum)
{
    const int n = weights.size();
    vector<bool> mask(k, true);
    mask.resize(n, false);
    vector<unsigned long long> result;
    do
    {
        int sum = 0;
        vector<int> cand;
        for (int i = 0; i < n; i++)
        {
            if (mask[i])
            {
                sum += weights[i];
                cand.push_back(weights[i]);
            }
        }

        if (sum == desiredSum)
        {
            result.emplace_back(quantumEntanglement(cand));
            printGroup(cand, k, sum);
        }
    } while (prev_permutation(mask.begin(), mask.end()));

    if (result.empty())
        return 0;

    return *min_element(result.begin(), result.end());
}

unsigned long long part1(vector<int> weights, int sum)
{
    printf("Part 1:\n");
    const int n = weights.size();
    const int desiredSum = sum / 3;
    printf("desired sum: %d\n", desiredSum);
    for (int i = 0; i < n; i++)
    {
        unsigned long long result = minEntanglement(weights, i, desiredSum);
        if (result > 0)
            return result;
    }

    return 0;
}

unsigned long long part2(vector<int> weights, int sum)
{
    printf("Part 2:\n");
    const int n = weights.size();
    const int desiredSum = sum / 4;
    printf("desired sum: %d\n", desiredSum);
    for (int i = 0; i < n; i++)
    {
        unsigned long long result = minEntanglement(weights, i, desiredSum);
        if (result > 0)
            return result;
    }

    return 0;
}

int main()
{
    const int n = 28;
    vector<int> weights;
    for (int i = 0; i < n; i++)
    {
        int weight;
        scanf("%d", &weight);
        weights.push_back(weight);
    }

    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += weights[i];
    }

    sort(weights.begin(), weights.end(), greater<int>());

    printf("qE = %llu\n", part1(weights, sum));
    printf("qE = %llu\n", part2(weights, sum));
}