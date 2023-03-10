#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

unsigned long long a = 0, b = 0;
int cursor = 0;

void run(const string& instruction)
{
    string inst = instruction.substr(0, 3);

    if (inst == "hlf") // Half
    {
        if (instruction[4] == 'a')
            a /= 2;
        else
            b /= 2;

        cursor++;
    }
    else if (inst == "tpl") // Triple
    {
        if (instruction[4] == 'a')
            a *= 3;
        else
            b *= 3;

        cursor++;
    }
    else if (inst == "inc") // Increment
    {
        if (instruction[4] == 'a')
            a++;
        else
            b++;

        cursor++;
    }
    else if (inst == "jmp") // Jump
    {
        int offset = stoi(instruction.substr(4));
        cursor += offset;
    }
    else if (inst == "jie") // Jump if even
    {
        if (instruction[4] == 'a')
        {
            if (a % 2 == 0)
                cursor += stoi(instruction.substr(7));
            else
                cursor++;
        }
        else
        {
            if (b % 2 == 0)
                cursor += stoi(instruction.substr(7));
            else
                cursor++;
        }
    }
    else if (inst == "jio") // Jump if one
    {
        if (instruction[4] == 'a')
        {
            if (a == 1)
                cursor += stoi(instruction.substr(7));
            else
                cursor++;
        }
        else
        {
            if (b == 1)
                cursor += stoi(instruction.substr(7));
            else
                cursor++;
        }
    }
}

void execute(const vector<string>& program)
{
    while (cursor < program.size())
    {
        run(program[cursor]);
    }
}

int main()
{
    vector<string> program;
    for (int i = 0; i < 47; i++)
    {
        string instruction;
        getline(cin, instruction);
        program.push_back(instruction);
    }

    // part 1
    a = 0; b = 0; cursor = 0;
    execute(program);
    printf("%llu\n", b);

    // part 2
    a = 1; b = 0; cursor = 0;
    execute(program);
    printf("%llu\n", b);
}
