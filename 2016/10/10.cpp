#include <math.h>
#include <stdio.h>
#include <string.h>

using namespace std;

struct bot
{
    int chip1 = 0;
    int chip2 = 0;
    int low = -1;
    int high = -1;
    int lowOut = -1;
    int highOut = -1;
};

struct value
{
    int val = 0;
    int dest = 0;
};

void receive(int chip, int i, bot* bots[210], int* out[21])
{
    bot* dest = bots[i];
    if (dest->chip1 == 0)
        dest->chip1 = chip;
    else if (dest->chip2 == 0)
        dest->chip2 = chip;

    if (dest->chip1 != 0 && dest->chip2 != 0)
    {
        if ((dest->chip1 == 61 && dest->chip2 == 17) || (dest->chip1 == 17 && dest->chip2 == 61))
        {
            printf("%d\n", i);
        }

        if (dest->low != -1)
            receive(min(dest->chip1, dest->chip2), dest->low, bots, out);

        if (dest->high != -1)
            receive(max(dest->chip1, dest->chip2), dest->high, bots, out);

        if (dest->lowOut != -1)
            *out[dest->lowOut] = min(dest->chip1, dest->chip2);

        if (dest->highOut != -1)
            *out[dest->highOut] = max(dest->chip1, dest->chip2);

        dest->chip1 = 0;
        dest->chip2 = 0;
    }
}

int main()
{
    bot* bots[210];
    for (int i = 0; i < 210; i++)
    {
        bots[i] = new bot();
    }

    int* out[21];
    for (int i = 0; i < 21; i++)
    {
        out[i] = (int*) malloc(sizeof(int));
        *out[i] = 0;
    }

    value vals[21];
    int ival = 0;
    for (int i = 0; i < 231; i++)
    {
        char firstWord[6];
        scanf("%s ", firstWord);
        if (strcmp(firstWord, "bot") == 0)
        {
            int botId, lowId, highId;
            char destLow[7], destHigh[7];
            scanf("%d gives low to %s %d and high to %s %d\n", &botId, destLow, &lowId, destHigh, &highId);
            if (strcmp(destLow, "bot") == 0)
            {
                bots[botId]->low = lowId;
            }
            else if (strcmp(destLow, "output") == 0)
            {
                bots[botId]->lowOut = lowId;
            }

            if (strcmp(destHigh, "bot") == 0)
            {
                bots[botId]->high = highId;
            }
            else if (strcmp(destHigh, "output") == 0)
            {
                bots[botId]->highOut = highId;
            }
        }
        else if (strcmp(firstWord, "value") == 0)
        {
            int val, dest;
            scanf("%d goes to bot %d\n", &val, &dest);
            vals[ival].val = val;
            vals[ival].dest = dest;
            ival++;
        }
    }

    for (int i = 0; i < 21; i++)
    {
        value v = vals[i];
        receive(v.val, v.dest, bots, out);
    }

    printf("%d\n", (*out[0]) * (*out[1]) * (*out[2]));
}
