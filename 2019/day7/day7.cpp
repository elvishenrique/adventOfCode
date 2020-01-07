#include <stdio.h>
#include <algorithm>
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

int proc(std::vector<std::vector<int>> mem, std::vector<int> shift)
{
    std::vector<bool> done = { false, false, false, false, false };
    std::vector<bool> ready = { true, false, false, false, false };
    int index = 0;
    std::vector<int> reg = { 0, 0, 0, 0, 0 };
    std::vector<int> pos = { 0, 0, 0, 0, 0 };
    std::vector<bool> phase = { true, true, true, true, true };
    while (std::find(done.begin(), done.end(), false) != done.end())
    {
        int inst = mem[index][pos[index]];
        switch (inst % 10)
        {
            case 1: // add
            {
                int x, y;
                std::tie(x, y) = getparams(mem[index], pos[index]);
                mem[index][mem[index][pos[index] + 3]] = x + y;
                pos[index] += 4;
                break;
            }
            case 2: // mul
            {
                int x, y;
                std::tie(x, y) = getparams(mem[index], pos[index]);
                mem[index][mem[index][pos[index] + 3]] = x * y;
                pos[index] += 4;
                break;
            }
            case 3: // input
            {
                if (phase[index])
                {
                    mem[index][mem[index][pos[index] + 1]] = shift[index];
                    phase[index] = false;
                    pos[index] += 2;
                }
                else if (ready[index])
                {
                    mem[index][mem[index][pos[index] + 1]] = reg[index];
                    ready[index] = false;
                    pos[index] += 2;
                }
                else
                {
                    index = (index + 1) % 5;
                }
                break;
            }
            case 4: // output
            {
                int o;
                std::tie(o, std::ignore) = getparams(mem[index], pos[index]);
                reg[(index + 1) % 5] = o;
                ready[(index + 1) % 5] = true;
                pos[index] += 2;
                break;
            }
            case 5: // jtrue
            {
                int x, y;
                std::tie(x, y) = getparams(mem[index], pos[index]);
                if (x != 0)
                    pos[index] = y;
                else
                    pos[index] += 3;
                break;
            }
            case 6: // jfalse
            {
                int x, y;
                std::tie(x, y) = getparams(mem[index], pos[index]);
                if (x == 0)
                    pos[index] = y;
                else
                    pos[index] += 3;
                break;
            }
            case 7: // lessthan
            {
                int x, y;
                std::tie(x, y) = getparams(mem[index], pos[index]);
                if (x < y)
                    mem[index][mem[index][pos[index] + 3]] = 1;
                else
                    mem[index][mem[index][pos[index] + 3]] = 0;
                pos[index] += 4;
                break;
            }
            case 8: // equals
            {
                int x, y;
                std::tie(x, y) = getparams(mem[index], pos[index]);
                if (x == y)
                    mem[index][mem[index][pos[index] + 3]] = 1;
                else
                    mem[index][mem[index][pos[index] + 3]] = 0;
                pos[index] += 4;
                break;
            }
            case 9:
            {
                if (inst == 99)
                {
                    done[index] = true;
                    index = (index + 1) % 5;
                }
                else
                {
                    printf("instruction error: %d\n", inst);
                    return -1;
                }
                break;
            }
            default:
            {
                printf("instruction error: %d\n", inst);
                return -1;
            }
        }
    }

    return reg[0];
}

int main()
{
    std::vector<std::vector<int>> mem;
    for (int i = 0; i < 5; i++)
    {
        mem.push_back(std::vector<int>());
    }

    for (int i = 0; i < 511; i++)
    {
        int p;
        scanf("%d,", &p);
        for (int i = 0; i < 5; i++)
        {
            mem[i].push_back(p);
        }
    }

    // std::vector<int> shift = { 0, 1, 2, 3, 4 }; // part 1
    std::vector<int> shift = { 5, 6, 7, 8, 9 }; // part 2

    int max = 0;
    do
    {
        int out = proc(mem, shift);
        if (out > max)
        {
            max = out;
        }
    } while (std::next_permutation(shift.begin(), shift.end()));

    printf("%d\n", max);
}