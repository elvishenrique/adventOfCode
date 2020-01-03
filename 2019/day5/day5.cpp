#include <stdio.h>
#include <tuple>
#include <utility>
#include <vector>

std::pair<int, int> getparams(std::vector<int> mem, int pos)
{
    int x, y, inst = mem[pos];

    // get x
    int xmode = (inst / 100) % 10;
    if (xmode == 0) // position
    {
        x = mem[mem[pos + 1]];
    }
    else if (xmode == 1) // immediate
    {
        x = mem[pos + 1];
    }
    else // error
    {
        printf("getparam: x mode error: %d\n", xmode);
        return std::make_pair(-1, -1);
    }

    // only 1 param
    if (inst % 10 == 3 || inst % 10 == 4)
        return std::make_pair(x, 0);

    // get y
    int ymode = (inst / 1000) % 10;
    if (ymode == 0) // position
    {
        y = mem[mem[pos + 2]];
    }
    else if (ymode == 1) // immediate
    {
        y = mem[pos + 2];
    }
    else // error
    {
        printf("getparam: y mode error: %d\n", ymode);
        return std::make_pair(-1, -1);
    }

    return std::make_pair(x, y);
}

bool proc(std::vector<int> mem)
{
    int pos = 0;
    while (mem[pos] != 99)
    {
        int inst = mem[pos];
        switch (inst % 10)
        {
            case 1: // add
            {
                int x, y;
                std::tie(x, y) = getparams(mem, pos);
                mem[mem[pos + 3]] = x + y;
                pos += 4;
                break;
            }
            case 2: // mul
            {
                int x, y;
                std::tie(x, y) = getparams(mem, pos);
                mem[mem[pos + 3]] = x * y;
                pos += 4;
                break;
            }
            case 3: // input
            {
                mem[mem[pos + 1]] = 5;
                pos += 2;
                break;
            }
            case 4: // output
            {
                int o;
                std::tie(o, std::ignore) = getparams(mem, pos);
                printf("%d\n", o);
                pos += 2;
                break;
            }
            case 5: // jtrue
            {
                int x, y;
                std::tie(x, y) = getparams(mem, pos);
                if (x != 0)
                    pos = y;
                else
                    pos += 3;
                break;
            }
            case 6: // jfalse
            {
                int x, y;
                std::tie(x, y) = getparams(mem, pos);
                if (x == 0)
                    pos = y;
                else
                    pos += 3;
                break;
            }
            case 7: // lessthan
            {
                int x, y;
                std::tie(x, y) = getparams(mem, pos);
                if (x < y)
                    mem[mem[pos + 3]] = 1;
                else
                    mem[mem[pos + 3]] = 0;
                pos += 4;
                break;
            }
            case 8: // equals
            {
                int x, y;
                std::tie(x, y) = getparams(mem, pos);
                if (x == y)
                    mem[mem[pos + 3]] = 1;
                else
                    mem[mem[pos + 3]] = 0;
                pos += 4;
                break;
            }
            default:
            {
                printf("instruction error: %d\n", inst);
                return false;
            }
        }
    }

    return true;
}

int main()
{
    std::vector<int> mem;
    for (int i = 0; i < 678; i++)
    {
        int p;
        scanf("%d,", &p);
        mem.push_back(p);
    }

    proc(mem);
}