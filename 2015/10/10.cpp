#include <stdio.h>
#include <string>

using namespace std;

string lookAndSay(const string& number)
{
    int counter = 1;
    char current = number[0];
    string result = "";
    for (int i = 1; i < number.size(); i++)
    {
        if (number[i] == current)
        {
            counter++;
        }
        else
        {
            result = result + to_string(counter) + current;
            current = number[i];
            counter = 1;
        }
    }

    result = result + to_string(counter) + current;

    return result;
}

int main() {
    string number = "1113122113";
    string ho = "1321132";
    string at = "1322113";
    for (int i = 0; i < 48; i++)
    {
        ho = lookAndSay(ho);
        at = lookAndSay(at);
    }

    printf("%lu\n", ho.size() + at.size());
}
