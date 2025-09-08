#include <iostream>
#include <set>
#include <stdio.h>

using namespace std;

int main()
{
    bool found = false;
    pair<int, int> destination;
    set<pair<int, int>> visited;
    visited.emplace(0, 0);
    int direction = 0, x = 0, y = 0;
    for (int i = 0; i < 169; i++)
    {
        char c;
        cin >> c;

        int d;
        cin >> d;

        direction = (c == 'R') ? (direction + 1) % 4 : (direction - 1) % 4;
        if (direction < 0)
            direction += 4;

        switch (direction)
        {
            case 0:
            {
                if (!found)
                {
                    for (int i = 1; i <= d; i++)
                    {
                        pair<int, int> position(x, y + i);
                        if (visited.find(position) != visited.end())
                        {
                            found = true;
                            destination = make_pair(x, y + i);
                        }
                        else
                        {
                            visited.emplace(x, y + i);
                        }
                    }
                }

                y += d;
                break;
            }
            case 1:
            {
                if (!found)
                {
                    for (int i = 1; i <= d; i++)
                    {
                        pair<int, int> position(x + i, y);
                        if (visited.find(position) != visited.end())
                        {
                            found = true;
                            destination = make_pair(x + i, y);
                        }
                        else
                        {
                            visited.emplace(x + i, y);
                        }
                    }
                }

                x += d;
                break;
            }
            case 2:
            {
                if (!found)
                {
                    for (int i = 1; i <= d; i++)
                    {
                        pair<int, int> position(x, y - i);
                        if (visited.find(position) != visited.end())
                        {
                            found = true;
                            destination = make_pair(x, y - i);
                        }
                        else
                        {
                            visited.emplace(x, y - i);
                        }
                    }
                }

                y -= d;
                break;
            }
            case 3:
            {
                if (!found)
                {
                    for (int i = 1; i <= d; i++)
                    {
                        pair<int, int> position(x - i, y);
                        if (visited.find(position) != visited.end())
                        {
                            found = true;
                            destination = make_pair(x - i, y);
                        }
                        else
                        {
                            visited.emplace(x - i, y);
                        }
                    }
                }

                x -= d;
                break;
            }
            default:
            {
                printf("%d\n", direction);
                break;
            }
        }
    }

    int distance = 0;
    distance = (x > 0) ? distance + x : distance - x;
    distance = (y > 0) ? distance + y : distance - y;
    printf("x: %d\ty: %d\tdistance: %d\n", x, y, distance);

    distance = 0; x = destination.first; y = destination.second;
    distance = (x > 0) ? distance + x : distance - x;
    distance = (y > 0) ? distance + y : distance - y;
    printf("destination:\nx: %d\ty:%d\tdistance:%d\n", x, y, distance);
}