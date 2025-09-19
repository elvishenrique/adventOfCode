#include <stdio.h>
#include <string>
#include <string.h>
#include <vector>

using namespace std;

string decompress(const string& input)
{
    vector<char> result;
    int n = input.size();
    for (int i = 0; i < n; i++)
    {
        if (input[i] == '(')
        {
            int x = input.find('x', i);
            int len = atoi(input.substr(i + 1, x - i - 1).c_str());
            int close = input.find(')', x);
            int reps = atoi(input.substr(x + 1, close - x - 1).c_str());
            for (int j = 0; j < reps; j++)
            {
                for (int k = 0; k < len; k++)
                {
                    result.push_back(input[close + 1 + k]);
                }
            }

            i = close + len;
        }
        else
        {
            result.push_back(input[i]);
        }
    }

    result.push_back(0);

    return result.data();
}

unsigned long long decompressv2(const string& input)
{
    size_t n = input.size();
    unsigned long long result = 0;
    for (int i = 0; i < n; i++)
    {
        if (input[i] == '(')
        {
            int x = input.find('x', i);
            int len = atoi(input.substr(i + 1, x - i - 1).c_str());
            int close = input.find(')', x);
            int reps = atoi(input.substr(x + 1, close - x - 1).c_str());
            result += reps * decompressv2(input.substr(close + 1, len));
            i = close + len;
        }
        else
        {
            result++;
        }
    }

    return result;
}

int main()
{
    char test1[7] = "ADVENT";
    char test2[9] = "A(1x5)BC";
    char test3[9] = "(3x3)XYZ";
    char test4[18] = "A(2x2)BCD(2x2)EFG";
    char test5[12] = "(6x1)(1x3)A";
    char test6[16] = "X(8x2)(3x3)ABCY";
    char test7[35] = "(27x12)(20x12)(13x14)(7x10)(1x12)A";
    char test8[57] = "(25x3)(3x3)ABC(2x3)XY(5x2)PQRSTX(18x9)(3x2)TWO(5x7)SEVEN";

    printf("%s\n", decompress(test1).c_str());
    printf("%s\n", decompress(test2).c_str());
    printf("%s\n", decompress(test3).c_str());
    printf("%s\n", decompress(test4).c_str());
    printf("%s\n", decompress(test5).c_str());
    printf("%s\n", decompress(test6).c_str());

    printf("%llu\n", decompressv2(test3));
    printf("%llu\n", decompressv2(test6));
    printf("%llu\n", decompressv2(test7));
    printf("%llu\n", decompressv2(test8));

    char input[11903];
    scanf("%s", input);
    printf("%lu\n", decompress(input).size());
    printf("%llu\n", decompressv2(input));
}