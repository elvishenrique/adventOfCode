#include <algorithm>
#include <stdio.h>
#include <unordered_map>

using namespace std;

unordered_map<int, int> weapons = {
    {4, 8}, // dagger
    {5, 10}, // shortsword
    {6, 25}, // warhammer
    {7, 40}, // longsword
    {8, 74} // greataxe
};

unordered_map<int, int> armor = {
    {1, 13}, // leather
    {2, 31}, // chainmail
    {3, 53}, // splintmail
    {4, 75}, // bandedmail
    {5, 102} // platemail
};

unordered_map<int, int> damrings = {
    {1, 25},
    {2, 50},
    {3, 100}
};

unordered_map<int, int> armrings = {
    {1, 20},
    {2, 40},
    {3, 80}
};

int min_cost(int attack, int defense)
{
    // Calculate attack candidates
    int ring_cost[3]; // min cost to reach target attack with given number of rings (0, 1 or 2)
    int max_ring_attack[3] = { 0, 3, 5 };
    vector<pair<int, int>> atk_cost_rings; // candidates for attack with pairs of cost and number of rings used.

    // Iterate through each weapon
    for (int w = 4; w <= 8; w++)
    {
        int ring_attack = attack - w;

        // If we surpass the target attack, we can reach it with lower cost, so no point in looking for stronger weapons.
        if (ring_attack < 0)
            break;

        // If we reached the target attack, only combination is with no rings.
        if (ring_attack == 0)
        {
            atk_cost_rings.push_back(make_pair(weapons[w], 0));
            break; // Stronger weapons will surpass the target attack, so no point in looking anymore.
        }

        if (ring_attack == 1)
        {
            atk_cost_rings.push_back(make_pair(weapons[w] + damrings[1], 1));
        }
        else if (ring_attack == 2)
        {
            atk_cost_rings.push_back(make_pair(weapons[w] + damrings[2], 1));
        }
        else if (ring_attack == 3)
        {
            atk_cost_rings.push_back(make_pair(weapons[w] + damrings[3], 1));
            atk_cost_rings.push_back(make_pair(weapons[w] + damrings[1] + damrings[2], 2));
        }
        else if (ring_attack == 4)
        {
            atk_cost_rings.push_back(make_pair(weapons[w] + damrings[1] + damrings[3], 2));
        }
        else if (ring_attack == 5)
        {
            atk_cost_rings.push_back(make_pair(weapons[w] + damrings[2] + damrings[3], 2));
        }
    }

    // Calculate defense candidates
    if (defense == 0)
    {
        // Return the option with least cost
        auto it = min_element(atk_cost_rings.begin(), atk_cost_rings.end(), [](const pair<int, int>& a, const pair<int, int>& b)
        {
            return a.first < b.first;
        });

        return it->first;
    }

    vector<pair<int, int>> def_cost_rings; // candidates for attack with pairs of cost and number of rings used.
    // Iterate through each armor (including no armor)
    for (int a = 0; a <= 5; a++)
    {
        int ring_defense = defense - a;

        // If we surpass the target defense, we can reach it with lower cost, so no point in looking for stronger armor.
        if (ring_defense < 0)
            break;

        // If we reached the target defense, only combination is with no rings.
        if (ring_defense == 0)
        {
            def_cost_rings.push_back(make_pair(armor[a], 0));
            break; // Stronger armor will surpass the target defense, so no point in looking anymore.
        }

        if (ring_defense == 1)
        {
            def_cost_rings.push_back(make_pair(armor[a] + armrings[1], 1));
        }
        else if (ring_defense == 2)
        {
            def_cost_rings.push_back(make_pair(armor[a] + armrings[2], 1));
        }
        else if (ring_defense == 3)
        {
            def_cost_rings.push_back(make_pair(armor[a] + armrings[3], 1));
            def_cost_rings.push_back(make_pair(armor[a] + armrings[1] + armrings[2], 2));
        }
        else if (ring_defense == 4)
        {
            def_cost_rings.push_back(make_pair(armor[a] + armrings[1] + armrings[3], 2));
        }
        else if (ring_defense == 5)
        {
            def_cost_rings.push_back(make_pair(armor[a] + armrings[2] + armrings[3], 2));
        }
    }

    // Combine the attack and defense candidates to find the lowest cost.
    int min_cost = 1000;
    for (const auto& atk : atk_cost_rings)
    {
        for (const auto& def : def_cost_rings)
        {
            if (atk.second + def.second <= 2) // Can have at most 2 rings.
            {
                if (atk.first + def.first < min_cost)
                {
                    min_cost = atk.first + def.first;
                }
            }
        }
    }

    return min_cost;
}

int max_cost(int attack, int defense)
{
    // Calculate attack candidates
    int ring_cost[3]; // min cost to reach target attack with given number of rings (0, 1 or 2)
    int max_ring_attack[3] = { 0, 3, 5 };
    vector<pair<int, int>> atk_cost_rings; // candidates for attack with pairs of cost and number of rings used.

    // Iterate through each weapon
    for (int w = 4; w <= 8; w++)
    {
        int ring_attack = attack - w;

        // Surpassed the target attack, stronger weapons won't be able to equal it, so don't look anymore.
        if (ring_attack < 0)
            break;

        // If we reached the target attack, only combination is with no rings.
        if (ring_attack == 0)
        {
            atk_cost_rings.push_back(make_pair(weapons[w], 0));
            break; // Stronger weapons will surpass the target attack, so no point in looking anymore.
        }

        if (ring_attack == 1)
        {
            atk_cost_rings.push_back(make_pair(weapons[w] + damrings[1], 1));
        }
        else if (ring_attack == 2)
        {
            atk_cost_rings.push_back(make_pair(weapons[w] + damrings[2], 1));
        }
        else if (ring_attack == 3)
        {
            atk_cost_rings.push_back(make_pair(weapons[w] + damrings[3], 1));
            atk_cost_rings.push_back(make_pair(weapons[w] + damrings[1] + damrings[2], 2));
        }
        else if (ring_attack == 4)
        {
            atk_cost_rings.push_back(make_pair(weapons[w] + damrings[1] + damrings[3], 2));
        }
        else if (ring_attack == 5)
        {
            atk_cost_rings.push_back(make_pair(weapons[w] + damrings[2] + damrings[3], 2));
        }
    }

    // Calculate defense candidates
    if (defense == 0)
    {
        // Return the option with most cost
        auto it = max_element(atk_cost_rings.begin(), atk_cost_rings.end(), [](const pair<int, int>& a, const pair<int, int>& b)
        {
            return a.first < b.first;
        });

        return it->first;
    }

    vector<pair<int, int>> def_cost_rings; // candidates for attack with pairs of cost and number of rings used.
    // Iterate through each armor (including no armor)
    for (int a = 0; a <= 5; a++)
    {
        int ring_defense = defense - a;

        // If we surpass the target defense, stronger weapons won't be able to equal it, so don't look anymore.
        if (ring_defense < 0)
            break;

        // If we reached the target defense, only combination is with no rings.
        if (ring_defense == 0)
        {
            def_cost_rings.push_back(make_pair(armor[a], 0));
            break; // Stronger armor will surpass the target defense, so no point in looking anymore.
        }

        if (ring_defense == 1)
        {
            def_cost_rings.push_back(make_pair(armor[a] + armrings[1], 1));
        }
        else if (ring_defense == 2)
        {
            def_cost_rings.push_back(make_pair(armor[a] + armrings[2], 1));
        }
        else if (ring_defense == 3)
        {
            def_cost_rings.push_back(make_pair(armor[a] + armrings[3], 1));
            def_cost_rings.push_back(make_pair(armor[a] + armrings[1] + armrings[2], 2));
        }
        else if (ring_defense == 4)
        {
            def_cost_rings.push_back(make_pair(armor[a] + armrings[1] + armrings[3], 2));
        }
        else if (ring_defense == 5)
        {
            def_cost_rings.push_back(make_pair(armor[a] + armrings[2] + armrings[3], 2));
        }
    }

    // Combine the attack and defense candidates to find the lowest cost.
    int max_cost = 0;
    for (const auto& atk : atk_cost_rings)
    {
        for (const auto& def : def_cost_rings)
        {
            if (atk.second + def.second <= 2) // Can have at most 2 rings.
            {
                if (atk.first + def.first > max_cost)
                {
                    max_cost = atk.first + def.first;
                }
            }
        }
    }

    return max_cost;
}

bool beats_boss(int boss_hp, int boss_attack, int boss_defense, int player_hp, int player_attack, int player_defense)
{
    int dpr = max(player_attack - boss_defense, 1);
    int sdpr = max(boss_attack - player_defense, 1);
    int rounds_to_win = (boss_hp % dpr == 0) ? boss_hp / dpr : (boss_hp / dpr) + 1;
    int rounds_to_lose = (player_hp % sdpr == 0) ? player_hp / sdpr : (player_hp / sdpr) + 1;

    return rounds_to_win <= rounds_to_lose;
}

int main()
{
    int boss_hp = 103, boss_attack = 9, boss_defense = 2, player_hp = 100, opt_cost = 1000, worst_cost = 0;
    for (int player_attack = 4; player_attack <= 13; player_attack++)
    {
        for (int player_defense = 0; player_defense <= 10; player_defense++)
        {
            if (beats_boss(boss_hp, boss_attack, boss_defense, player_hp, player_attack, player_defense))
            {
                int cost = min_cost(player_attack, player_defense);
                if (cost < opt_cost)
                    opt_cost = cost;
            }
            else
            {
                int cost = max_cost(player_attack, player_defense);
                if (cost > worst_cost)
                    worst_cost = cost;
            }
        }
    }

    printf("optimal cost: %d\tworst cost: %d\n", opt_cost, worst_cost);
}