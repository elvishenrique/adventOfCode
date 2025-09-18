#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

bool hasAbba(const string& s)
{
    int n = s.size();
    if (n < 4)
        return false;

    for (int i = 3; i < n; i++)
    {
        if (s[i] == s[i - 3] && s[i - 1] == s[i - 2] && s[i] != s[i - 1])
            return true;
    }

    return false;
}

bool hasOuterAbba(const string& ip)
{
    if (ip.empty()) return false;
    auto open = ip.find('[');
    auto close = ip.find(']');
    const string& outer = ip.substr(0, open);
    const string& remainder = (close == string::npos) ? "" : ip.substr(close + 1);
    return hasAbba(outer) || hasOuterAbba(remainder);
}

bool hasInnerAbba(const string& ip)
{
    if (ip.empty()) return false;
    auto open = ip.find('[');
    auto close = ip.find(']');
    const string& inner = (open == string::npos) ? "" : ip.substr(open + 1, close - open - 1);
    const string& remainder = (close == string::npos) ? "" : ip.substr(close + 1);
    return hasAbba(inner) || hasInnerAbba(remainder);
}

bool supportsTLS(const string& ip)
{
    return hasOuterAbba(ip) && !hasInnerAbba(ip);
}

vector<string> babs(const string& outer)
{
    vector<string> result;
    int n = outer.size();
    if (n < 3) return result;

    for (int i = 2; i < n; i++)
    {
        if (outer[i] == outer[i - 2] && outer[i] != outer[i - 1])
        {
            string bab({ outer [i -1], outer[i], outer[i - 1] });
            result.push_back(bab);
        }
    }

    return result;
}

bool supportsSSL(const string& ip)
{
    vector<string> outers, inners;
    size_t open = 0, close = 0, n = ip.size();
    while (open < n && close < n)
    {
        if (close == 0)
            open = ip.find('[');
        else if (close < n - 1)
            open = ip.find('[', close + 1);

        if (close == 0)
            outers.push_back(ip.substr(0, open));
        else if (close < n - 1)
            outers.push_back(ip.substr(close + 1, open - close - 1));

        close = ip.find(']', open + 1);
        if (open < n - 1)
            inners.push_back(ip.substr(open + 1, close - open - 1));
    }

    vector<string> totalBabs;
    for (const string& outer : outers)
    {
        vector<string> outerBabs = babs(outer);
        totalBabs.insert(totalBabs.end(), outerBabs.begin(), outerBabs.end());
    }

    for (const string& bab : totalBabs)
    {
        for (const string& inner : inners)
        {
            if (inner.find(bab) != string::npos) return true;
        }
    }

    return false;
}

int main ()
{
    int part1 = 0, part2 = 0;
    for (int i = 0; i < 2000; i++)
    {
        char ip[200];
        scanf("%s\n", ip);
        if (supportsTLS(ip))
            part1++;

        if (supportsSSL(ip))
            part2++;
    }

    printf("part1: %d\npart2: %d\n", part1, part2);
}