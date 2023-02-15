#include <iostream>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct Reindeer
{
public:
    Reindeer(const string& n, int s, int f, int r)
    : name(n)
    , speed(s)
    , flyTime(f)
    , restTime(r)
    {
        cycleTime = f + r;
        distance = s * f;
        points = 0;
    }

    int traveled(int time)
    {
        int result = 0;
        int cycles = time / cycleTime;
        result += distance * cycles;
        if (time % cycleTime > flyTime)
            result += distance;
        else
            result += speed * (time % cycleTime);

        return result;
    }

    void score()
    {
        points++;
    }

    string name;
    int speed;
    int flyTime;
    int restTime;
    int cycleTime;
    int distance;
    int points;
};

vector<Reindeer> reindeers;

void parse(const string& line)
{
    string::size_type canPos = line.find(" can fly ");
    string::size_type kmsPos = line.find(" km/s for ");
    string::size_type flyTimePos = line.find(" seconds, ");
    string::size_type restPos = line.find(" rest for ");
    string::size_type restTimePos = line.find(" seconds.");
    string reindeer = line.substr(0, canPos);
    int speed = stoi(line.substr(canPos + 9, kmsPos - canPos - 9));
    int flyTime = stoi(line.substr(kmsPos + 10, flyTimePos - kmsPos - 10));
    int restTime = stoi(line.substr(restPos + 10, restTimePos - restPos - 10));

    reindeers.emplace_back(reindeer, speed, flyTime, restTime);
}

int main()
{
    for (int i = 0; i < 9; i++)
    {
        string line;
        getline(cin, line);
        parse(line);
    }

    int max = 0;
    for (int i = 0; i < 9; i++)
    {
        int tr = reindeers[i].traveled(2503);
        if (tr > max)
            max = tr;
    }

    printf("%d\n", max);

    for (int t = 1; t <= 2503; t++)
    {
        int lead = 0;
        for (int i = 0; i < 9; i++)
        {
            int pos = reindeers[i].traveled(t);
            if (pos > lead)
                lead = pos;
        }

        for (int i = 0; i < 9; i++)
        {
            if (reindeers[i].traveled(t) == lead)
                reindeers[i].score();
        }
    }

    int win = 0;
    for (int i = 0; i < 9; i++)
    {
        if (reindeers[i].points > win)
            win = reindeers[i].points;
    }

    printf("%d\n", win);
}