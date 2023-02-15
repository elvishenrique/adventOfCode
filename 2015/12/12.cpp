#include <iostream>
#include <string>
#include <string.h>

using namespace std;

int sum(const string& json)
{
    int result = 0;
    int sign = 1;
    int current = 0;
    for (int i = 0; i < json.size(); i++)
    {
        if (json[i] == '-')
        {
            sign = -1;
        }
        else if (isdigit(json[i]))
        {
            current = 10*current + json[i] - '0';
        }
        else if (current != 0)
        {
            result += sign * current;
            current = 0;
            sign = 1;
        }
    }

    return result;
}

int get_number(const string& json, int* start)
{
    int result = 0, sign = 1, i = *start;
    if (json[i] == '-')
    {
        sign = -1;
        i++;
    }

    while (isdigit(json[i]))
    {
        result = 10 * result + json[i] - '0';
        i++;
    }

    result *= sign;
    *start = i;

    return result;
}

enum Level
{
    PROPERTY,
    VALUE,
    ARRAY,
    SUBOBJECT,
};

int redless_sum(const string& json, int* start)
{
    int result = 0, i = *start;

    // If this is a ',', just move forward
    if (json[i] == ',')
    {
        *start = i + 1;
        return 0;
    }

    // If this is an array, iterate over its values
    if (json[i] == '[')
    {
        i++;
        while (json[i] != ']')
        {
            if (json[i] == ',') // It's the ','. Just move forward.
            {
                i++;
            }
            else if (json[i] == '-' || isdigit(json[i])) // It's a number.
            {
                result += get_number(json, &i);
            }
            else if (json[i] == '\"') // It's a string. Skip it.
            {
                // Move i forward so we're at the ',' or ']'.
                for ( ; json[i] != ',' && json[i] != ']'; i++);
            }
            else if (json[i] == '[' || json[i] == '{') // It's an array or subobject. Calculate value and move forward.
            {
                result += redless_sum(json, &i);
            }
        }

        // Move forward so we're past the array.
        *start = i + 1;
        return result;
    }

    // If this is an object, iterate over its properties
    if (json[i] == '{')
    {
        bool hasRed = false;
        i++;
        while (json[i] != '}')
        {
            if (json[i] == ',') // It's the ','. Just move forward.
            {
                i++;
            }
            else if (json[i] == '\"') // It's a property. Check if it's value is red or calculate its value.
            {
                // Get to the ':' so we can check its value.
                for ( ; json[i] != ':'; i++);

                // Move forward to parse the value.
                i++;

                if (json[i] == '-' || isdigit(json[i])) // It's a number.
                {
                    result += get_number(json, &i);
                }
                else if (json[i] == '\"') // It's a string. Look for red.
                {
                    if (i + 4 < json.size() && json[i + 1] == 'r' && json[i + 2] == 'e' && json[i + 3] == 'd' && json[i + 4] == '\"')
                    {
                        hasRed = true;
                    }

                    // We don't care about strings otherwise, move forward to the next property.
                    for ( ; json[i] != ',' && json[i] != '}'; i++);
                }
                else if (json[i] == '[' || json[i] == '{') // It's an array or subobject. Calculate value and move forward.
                {
                    result += redless_sum(json, &i);
                }
            }
        }

        *start = i + 1;
        return hasRed ? 0 : result;
    }

    printf("Wrong string: %c\ti: %d\n", json[i], i);
    return 0;
}

int main()
{
    string json;
    getline(cin, json);
    printf("%d\n", sum(json));

    int start = 0;
    printf("%d\n", redless_sum(json, &start));
}
