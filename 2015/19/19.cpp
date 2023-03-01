#include <iostream>
#include <queue>
#include <stdio.h>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

pair<string, string> parse(const string& line)
{
    string::size_type arrPos = line.find(" => ");
    return make_pair(line.substr(0, arrPos), line.substr(arrPos + 4));
}

int rbfs(const string& target, const vector<pair<string, string>>& replacements)
{
    string e = "e";
    if (target == e)
        return 0;

    // Auxiliary queue with molecules and steps needed to make them.
    queue<pair<string, int>> q;
    q.push(make_pair(target, 0));

    // Auxiliary queue with molecules and steps needed to make them.
    unordered_set<string> made;
    made.insert(target);
    while (!q.empty())
    {
        string current = q.front().first; // Current molecule to make new molecules.
        // printf("%lu\n", current.size());
        int steps = q.front().second; // Number of steps necessary to make the current molecule.
        printf("steps: %d, string: %s\n", steps, current.c_str());
        // Generate all unique molecules from current
        for (const auto& repl : replacements)
        {
            string::size_type atomPos = 0;
            string source = current.substr(atomPos);
            while (atomPos != string::npos)
            {
                atomPos = source.find(repl.first);
                string::size_type offset = current.size() - source.size();
                if (atomPos != string::npos)
                {
                    string gen = current.substr(0, atomPos + offset) + repl.second + current.substr(atomPos + offset + repl.first.size());

                    // If we made the target, we're done, add 1 step to the result to account for this.
                    if (gen == e)
                        return steps + 1;

                    if (!made.contains(gen))
                    {
                        made.insert(gen);
                        q.push(make_pair(gen, steps + 1));
                    }

                    source = source.substr(atomPos + repl.first.size());
                }
            }
        }

        q.pop();
    }

    // Couldn't find target
    return -1;
}

int bfs(const string& target, const vector<pair<string, string>>& replacements)
{
    string e = "e";
    if (target == e)
        return 0;

    // Auxiliary queue with molecules and steps needed to make them.
    queue<pair<string, int>> q;
    q.push(make_pair(e, 0));

    // Auxiliary queue with molecules and steps needed to make them.
    unordered_set<string> made;
    made.insert(e);
    while (!q.empty())
    {
        string current = q.front().first; // Current molecule to make new molecules.
        // printf("%lu\n", current.size());
        int steps = q.front().second; // Number of steps necessary to make the current molecule.
        printf("steps: %d, string: %s\n", steps, current.c_str());
        // Generate all unique molecules from current
        for (const auto& repl : replacements)
        {
            string::size_type atomPos = 0;
            string source = current.substr(atomPos);
            while (atomPos != string::npos)
            {
                atomPos = source.find(repl.first);
                string::size_type offset = current.size() - source.size();
                if (atomPos != string::npos)
                {
                    string gen = current.substr(0, atomPos + offset) + repl.second + current.substr(atomPos + offset + repl.first.size());

                    // If we made the target, we're done, add 1 step to the result to account for this.
                    if (gen == target)
                        return steps + 1;

                    if (!made.contains(gen))
                    {
                        made.insert(gen);
                        q.push(make_pair(gen, steps + 1));
                    }

                    source = source.substr(atomPos + repl.first.size());
                }
            }
        }

        q.pop();
    }

    // Couldn't find target
    return -1;
}

int decay_mol(const string& source, const vector<pair<string, string>>& reversements)
{
    string e = "e";
    string current = source;
    int steps = 0;
    while (current != e)
    {
        for (const auto& rev : reversements)
        {
            string::size_type molPos = current.find(rev.first);
            if (molPos != string::npos)
            {
                printf("%s\n", current.c_str());
                current = current.substr(0, molPos) + rev.second + current.substr(molPos + rev.first.size());
                steps++;
                // get back to loop reversements from the beginning.
                break;
            }
        }
    }

    printf("%s\n", current.c_str());

    return steps;
}

int main()
{
    vector<pair<string, string>> replacements;
    vector<pair<string, string>> reversements;
    // for (int i = 0; i < 5; i++)
    for (int i = 0; i < 43; i++)
    {
        string line;
        getline(cin, line);
        pair<string, string> repl = parse(line);
        replacements.push_back(repl);
        reversements.push_back(make_pair(repl.second, repl.first));
    }

    string molecule;
    getline(cin, molecule);
    getline(cin, molecule);

    unordered_set<string> generated;
    for (const auto& repl : replacements)
    {
        string::size_type atomPos = 0;
        string source = molecule.substr(atomPos);
        while (atomPos != string::npos)
        {
            atomPos = source.find(repl.first);
            string::size_type offset = molecule.size() - source.size();
            if (atomPos != string::npos)
            {
                string gen = molecule.substr(0, atomPos + offset) + repl.second + molecule.substr(atomPos + offset + repl.first.size());
                generated.insert(gen);
                source = source.substr(atomPos + repl.first.size());
            }
        }
    }

    printf("%lu\n", generated.size());

    sort(reversements.begin(), reversements.end(), [](const pair<string, string>& a, const pair<string, string>& b)
    {
        return a.first.size() > b.first.size();
    });

    for (const auto& repl : reversements)
    {
        printf("%s => %s\n", repl.second.c_str(), repl.first.c_str());
    }

    printf("%d\n", decay_mol(molecule, reversements));

    //printf("%d\n", bfs(molecule, replacements));
}