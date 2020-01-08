#include <stdio.h>
#include <tuple>
#include <utility>
#include <vector>

void complete(std::vector<long long>& mem, long long index)
{
    if (index >= mem.size())
    {
        for (long long i = mem.size(); i <= index; i++)
        {
            mem.push_back(0);
        }
    }
}

std::pair<long long, long long> getparams(std::vector<long long>& mem, long long pos, long long rel)
{
    long long x, y, inst = mem[pos];

    // get x
    long long xmode = (inst / 100) % 10;
    if (xmode == 0) // position
    {
        complete(mem, mem[pos + 1]);
        x = mem[mem[pos + 1]];
    }
    else if (xmode == 1) // immediate
    {
        complete(mem, pos + 1);
        x = mem[pos + 1];
    }
    else if (xmode == 2) // relative
    {
        complete(mem, mem[pos + 1] + rel);
        x = mem[mem[pos + 1] + rel];
    }
    else // error
    {
        printf("getparam: x mode error: %lld\n", xmode);
        return std::make_pair(-1, -1);
    }

    // only 1 param
    if (inst % 10 == 3 || inst % 10 == 4 || inst % 10 == 9)
        return std::make_pair(x, 0);

    // get y
    long long ymode = (inst / 1000) % 10;
    if (ymode == 0) // position
    {
        complete(mem, mem[pos + 2]);
        y = mem[mem[pos + 2]];
    }
    else if (ymode == 1) // immediate
    {
        complete(mem, pos + 2);
        y = mem[pos + 2];
    }
    else if (ymode == 2) // relative
    {
        complete(mem, mem[pos + 2] + rel);
        y = mem[mem[pos + 2] + rel];
    }
    else // error
    {
        printf("getparam: y mode error: %lld\n", ymode);
        return std::make_pair(-1, -1);
    }

    return std::make_pair(x, y);
}

bool proc(std::vector<long long> mem, long long input)
{
    long long pos = 0, rel = 0;
    while (mem[pos] != 99)
    {
        long long inst = mem[pos];
        switch (inst % 10)
        {
            case 1: // add
            {
                long long x, y;
                std::tie(x, y) = getparams(mem, pos, rel);

                int zmode = (inst / 10000) % 10;
                if (zmode == 0) // position
                {
                    complete(mem, mem[pos + 3]);
                    mem[mem[pos + 3]] = x + y;
                }
                else if (zmode == 2) // relative
                {
                    complete(mem, mem[pos + 3] + rel);
                    mem[mem[pos + 3] + rel] = x + y;
                }
                else // error
                {
                    printf("zmode error: %lld\n", inst);
                    return false;
                }

                pos += 4;
                break;
            }
            case 2: // mul
            {
                long long x, y;
                std::tie(x, y) = getparams(mem, pos, rel);

                int zmode = (inst / 10000) % 10;
                if (zmode == 0) // position
                {
                    complete(mem, mem[pos + 3]);
                    mem[mem[pos + 3]] = x * y;
                }
                else if (zmode == 2) // relative
                {
                    complete(mem, mem[pos + 3] + rel);
                    mem[mem[pos + 3] + rel] = x * y;
                }
                else // error
                {
                    printf("zmode error: %lld\n", inst);
                    return false;
                }

                pos += 4;
                break;
            }
            case 3: // input
            {
                int zmode = (inst / 100) % 10;
                if (zmode == 0) // position
                {
                    complete(mem, mem[pos + 1]);
                    mem[mem[pos + 1]] = input;
                }
                else if (zmode == 2) // relative
                {
                    complete(mem, mem[pos + 1] + rel);
                    mem[mem[pos + 1] + rel] = input;
                }
                else // error
                {
                    printf("zmode error: %lld\n", inst);
                    return false;
                }

                pos += 2;
                break;
            }
            case 4: // output
            {
                long long o;
                std::tie(o, std::ignore) = getparams(mem, pos, rel);
                printf("%lld\n", o);
                pos += 2;
                break;
            }
            case 5: // jtrue
            {
                long long x, y;
                std::tie(x, y) = getparams(mem, pos, rel);
                if (x != 0)
                    pos = y;
                else
                    pos += 3;
                break;
            }
            case 6: // jfalse
            {
                long long x, y;
                std::tie(x, y) = getparams(mem, pos, rel);
                if (x == 0)
                    pos = y;
                else
                    pos += 3;
                break;
            }
            case 7: // lessthan
            {
                long long x, y;
                std::tie(x, y) = getparams(mem, pos, rel);

                long long index = -1;
                int zmode = (inst / 10000) % 10;
                if (zmode == 0) // position
                {
                    index = mem[pos + 3];
                }
                else if (zmode == 2) // relative
                {
                    index = mem[pos + 3] + rel;
                }
                else // error
                {
                    printf("zmode error: %lld\n", inst);
                    return false;
                }

                complete(mem, index);
                if (x < y)
                    mem[index] = 1;
                else
                    mem[index] = 0;
                pos += 4;
                break;
            }
            case 8: // equals
            {
                long long x, y;
                std::tie(x, y) = getparams(mem, pos, rel);

                long long index = -1;
                int zmode = (inst / 10000) % 10;
                if (zmode == 0) // position
                {
                    index = mem[pos + 3];
                }
                else if (zmode == 2) // relative
                {
                    index = mem[pos + 3] + rel;
                }
                else // error
                {
                    printf("zmode error: %lld\n", inst);
                    return false;
                }

                complete(mem, index);
                if (x == y)
                    mem[index] = 1;
                else
                    mem[index] = 0;
                pos += 4;
                break;
            }
            case 9: // setrel
            {
                long long x;
                std::tie(x, std::ignore) = getparams(mem, pos, rel);
                rel += x;
                pos += 2;
                break;
            }
            default:
            {
                printf("instruction error: %lld\n", inst);
                return false;
            }
        }

        complete(mem, pos + 3);
    }

    return true;
}

int main()
{
    std::vector<long long> mem;
    for (int i = 0; i < 973; i++)
    {
        int p;
        scanf("%d,", &p);
        mem.push_back(p);
    }

    proc(mem, 1);
    proc(mem, 2);
}