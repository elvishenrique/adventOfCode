#include <stdio.h>
#include <string>

using namespace std;

string increment(const string& password)
{
    char result[8];
    for (int i = 0; i < 8; i++)
    {
        result[i] = password[i];
    }

    bool finished = false;
    int digit = 7;
    while (digit >= 0)
    {
        if (result[digit] != 'z')
        {
            result[digit] += 1;
            break;
        }
        else
        {
            result[digit] = 'a';
            digit--;
        }
    }

    return result;
}

bool sequence(const string& password)
{
    for (int i = 0; i < 6; i++)
    {
        if (password[i + 1] == password[i] + 1 && password[i + 2] == password[i] + 2)
            return true;
    }

    return false;
}

string fix_letters(const string& password)
{
    char result[8];
    for (int i = 0; i < 8; i++)
    {
        if (password[i] == 'i' || password[i] == 'l' || password[i] == 'o')
        {
            result[i] = password[i] + 1;
            for (int j = i + 1; j < 8; j++)
            {
                if (j < 8)
                {
                    result[j] = 'a';
                }
            }

            return result;
        }
        else
        {
            result[i] = password[i];
        }
    }

    return result;
}

bool double_letters(const string& password)
{
    int doubles = 0;
    char doubleChar;
    for (int i = 0; i < 7; i++)
    {
        if (password[i] == password[i + 1])
        {
            if (doubles == 0)
            {
                doubleChar = password[i];
                doubles++;
                i += 1;
            }
            else if (password[i] != doubleChar)
            {
                return true;
            }
        }
    }

    return doubles > 1;
}

int main()
{
    bool valid = false;
    string password = "hxbxwxba";
    while (!valid)
    {
        password = fix_letters(increment(password));
        if (sequence(password) && double_letters(password))
            valid = true;
    }

    printf("%s\n", password.c_str());

    valid = false;
    while (!valid)
    {
        password = fix_letters(increment(password));
        if (sequence(password) && double_letters(password))
            valid = true;
    }

    printf("%s\n", password.c_str());
}
