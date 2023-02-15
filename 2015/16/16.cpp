#include <iostream>
#include <optional>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct Sue
{
public:
    Sue(int i, optional<int> chi, optional<int> cat, optional<int> sam, optional<int> pom, optional<int> aki, optional<int> viz, optional<int> gol, optional<int> tre, optional<int> car, optional<int> per)
    : index(i)
    , children(chi)
    , cats(cat)
    , samoyeds(sam)
    , pomeranians(pom)
    , akitas(aki)
    , vizslas(viz)
    , goldfish(gol)
    , trees(tre)
    , cars(car)
    , perfumes(per)
    {
    }

    int index;
    optional<int> children;
    optional<int> cats;
    optional<int> samoyeds;
    optional<int> pomeranians;
    optional<int> akitas;
    optional<int> vizslas;
    optional<int> goldfish;
    optional<int> trees;
    optional<int> cars;
    optional<int> perfumes;
};

vector<Sue> sues;

void parse(const string& line)
{
    string::size_type chiPos = line.find("children: ");
    string::size_type catPos = line.find("cats: ");
    string::size_type samPos = line.find("samoyeds: ");
    string::size_type pomPos = line.find("pomeranians: ");
    string::size_type akiPos = line.find("akitas: ");
    string::size_type vizPos = line.find("vizslas: ");
    string::size_type golPos = line.find("goldfish: ");
    string::size_type trePos = line.find("trees: ");
    string::size_type carPos = line.find("cars: ");
    string::size_type perPos = line.find("perfumes: ");
    int i = stoi(line.substr(4));
    optional<int> chi = chiPos != string::npos ? optional<int>(stoi(line.substr(chiPos + 10))) : nullopt;
    optional<int> cat = catPos != string::npos ? optional<int>(stoi(line.substr(catPos + 6))) : nullopt;
    optional<int> sam = samPos != string::npos ? optional<int>(stoi(line.substr(samPos + 10))) : nullopt;
    optional<int> pom = pomPos != string::npos ? optional<int>(stoi(line.substr(pomPos + 13))) : nullopt;
    optional<int> aki = akiPos != string::npos ? optional<int>(stoi(line.substr(akiPos + 8))) : nullopt;
    optional<int> viz = vizPos != string::npos ? optional<int>(stoi(line.substr(vizPos + 9))) : nullopt;
    optional<int> gol = golPos != string::npos ? optional<int>(stoi(line.substr(golPos + 10))) : nullopt;
    optional<int> tre = trePos != string::npos ? optional<int>(stoi(line.substr(trePos + 7))) : nullopt;
    optional<int> car = carPos != string::npos ? optional<int>(stoi(line.substr(carPos + 6))) : nullopt;
    optional<int> per = perPos != string::npos ? optional<int>(stoi(line.substr(perPos + 10))) : nullopt;

    sues.emplace_back(i, chi, cat, sam, pom, aki, viz, gol, tre, car, per);
}

int main()
{
    for (int i = 0; i < 500; i++)
    {
        string line;
        getline(cin, line);
        parse(line);
    }

    for (const auto& sue : sues)
    {
        if (sue.children.has_value() && sue.children.value() != 3)
            continue;

        if (sue.cats.has_value() && sue.cats.value() <= 7)
            continue;

        if (sue.samoyeds.has_value() && sue.samoyeds.value() != 2)
            continue;

        if (sue.pomeranians.has_value() && sue.pomeranians.value() >= 3)
            continue;

        if (sue.akitas.has_value() && sue.akitas.value() != 0)
            continue;

        if (sue.vizslas.has_value() && sue.vizslas.value() != 0)
            continue;

        if (sue.goldfish.has_value() && sue.goldfish.value() >= 5)
            continue;

        if (sue.trees.has_value() && sue.trees.value() <= 3)
            continue;

        if (sue.cars.has_value() && sue.cars.value() != 2)
            continue;

        if (sue.perfumes.has_value() && sue.perfumes.value() != 1)
            continue;

        printf("%d\n", sue.index);
    }
}
