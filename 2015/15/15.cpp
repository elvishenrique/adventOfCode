#include <iostream>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct Ingredient
{
public:
    Ingredient(const string& n, int cap, int dur, int fla, int tex, int cal)
    : name(n)
    , capacity(cap)
    , durability(dur)
    , flavor(fla)
    , texture(tex)
    , calories(cal)
    {
    }

    string name;
    int capacity;
    int durability;
    int flavor;
    int texture;
    int calories;
};

vector<Ingredient> ingredients;

int score(const vector<int>& recipe)
{
    int capacity = 0, durability = 0, flavor = 0, texture = 0;
    for (int i = 0; i < ingredients.size(); i++)
    {
        capacity += recipe[i] * ingredients[i].capacity;
        durability += recipe[i] * ingredients[i].durability;
        flavor += recipe[i] * ingredients[i].flavor;
        texture += recipe[i] * ingredients[i].texture;
    }

    if (capacity <= 0 || durability <= 0 || flavor <= 0 || texture <= 0)
        return 0;

    return capacity * durability * flavor * texture;
}

int calories(const vector<int>& recipe)
{
    int calories = 0;
    for (int i = 0; i < ingredients.size(); i++)
    {
        calories += recipe[i] * ingredients[i].calories;
    }

    return calories;
}

void parse(const string& line)
{
    string::size_type capPos = line.find(": capacity ");
    string::size_type durPos = line.find(", durability ");
    string::size_type flaPos = line.find(", flavor ");
    string::size_type texPos = line.find(", texture ");
    string::size_type calPos = line.find(", calories ");
    string ingredient = line.substr(0, capPos);
    int cap = stoi(line.substr(capPos + 11, durPos - capPos - 11));
    int dur = stoi(line.substr(durPos + 13, flaPos - durPos - 13));
    int fla = stoi(line.substr(flaPos + 9, texPos - flaPos - 9));
    int tex = stoi(line.substr(texPos + 10, calPos - texPos - 10));
    int cal = stoi(line.substr(calPos + 11));

    ingredients.emplace_back(ingredient, cap, dur, fla, tex, cal);
}

int main()
{
    for (int i = 0; i < 4; i++)
    {
        string line;
        getline(cin, line);
        parse(line);
    }

    int max = 0, healthy = 0;
    for (int i = 0; i <= 100 ; i++)
    {
        for (int j = 0; j <= 100 - i; j++)
        {
            for (int k = 0; k <= 100 - i - j; k++)
            {
                vector<int> recipe = { i, j, k, 100 - i - j - k };
                int s = score(recipe);
                if (s > max)
                    max = s;

                if (s > healthy && calories(recipe) == 500)
                    healthy = s;
            }
        }
    }

    printf("%d\n", max);
    printf("%d\n", healthy);
}
